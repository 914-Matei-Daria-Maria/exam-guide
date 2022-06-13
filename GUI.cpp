#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QMessageBox>
#include "GUI.h"

GUI::GUI(Service &service, User& user) : service(service), user(user)
{
    this->setWindowTitle((user.getName() + ", " + user.getType()).c_str());
    this->mainLayout = new QVBoxLayout(this);
    this->createIssuesList();

    this->service.addObserver(this);

    if (user.getType() == "tester")
    {
        this->createAddIssue();
    }
    else
    {
        this->createResolveIssue();
    }
    this->createRemoveIssue();
    this->connectSignalsAndSlots();
}

void GUI::createIssuesList()
{
    this->issuesList = new QListWidget();

    this->populateIssuesList();

    this->mainLayout->addWidget(this->issuesList);
}

void GUI::populateIssuesList()
{
    if (this->issuesList->count() > 0)
        this->issuesList->clear();

    this->issuesSorted = service.getIssuesSorted();
    for (auto issue : this->issuesSorted)
    {
        std::string issueStr = issue.toString();
        auto* issueItem = new QListWidgetItem(QString::fromStdString(issueStr));
        this->issuesList->addItem(issueItem);
    }

    if (this->issuesList->count() > 0)
        this->issuesList->setCurrentRow(0);
}

void GUI::createAddIssue()
{
    this->addButton = new QPushButton("Add issue");
    auto addLabel = new QLabel("Issue description:");
    this->addEdit = new QLineEdit;
    auto addWidget = new QWidget;
    auto addLayout = new QHBoxLayout(addWidget);
    addLayout->addWidget(addLabel);
    addLayout->addWidget(this->addEdit);
    addLayout->addWidget(this->addButton);
    addWidget->setLayout(addLayout);
    this->mainLayout->addWidget(addWidget);
}

void GUI::connectSignalsAndSlots()
{
    if (user.getType() == "tester")
    {
        QObject::connect(this->addButton, &QPushButton::clicked, this, &GUI::addIssueHandler);
    }
    else
    {
        QObject::connect(this->resolveButton, &QPushButton::clicked, this, &GUI::resolveIssueHandler);
        QObject::connect(this->issuesList, &QListWidget::itemSelectionChanged, this,
                         &GUI::listItemSelectionChangedHandler);
    }
    QObject::connect(this, &GUI::issuesUpdatedSignal, this, &GUI::populateIssuesList);
    QObject::connect(this->removeButton, &QPushButton::clicked, this, &GUI::removeIssueHandler);
}

void GUI::addIssueHandler()
{
    std::string description = this->addEdit->text().toStdString();

    std::string userName = this->user.getName();
    try
    {
        this->service.addIssue(description, userName);
        emit issuesUpdatedSignal();
    }
    catch (std::runtime_error& runtimeError)
    {
        QMessageBox::critical(this, "Error", runtimeError.what());
    }
}

void GUI::createRemoveIssue()
{
    this->removeButton = new QPushButton("Remove selected issue");
    this->mainLayout->addWidget(this->removeButton);
}

void GUI::removeIssueHandler()
{
    int i = this->getSelectedIndex();

    if (i == -1)
        return;

    try
    {
        Issue issue = this->issuesSorted[i];
        this->service.removeIssue(this->service.getIssuePos(issue));
        emit issuesUpdatedSignal();
    }
    catch(std::runtime_error& runtimeError)
    {
        QMessageBox::critical(this, "Error", runtimeError.what());
    }
}

int GUI::getSelectedIndex()
{
    if (this->issuesList->count() == 0)
        return -1;

    QModelIndexList index = this->issuesList->selectionModel()->selectedIndexes();
    if (index.size() == 0)
        return -1;

    int i = index.at(0).row();
    return i;
}

void GUI::createResolveIssue()
{
    this->resolveButton = new QPushButton("Resolve selected issue");
    this->resolveButton->setEnabled(false);
    this->mainLayout->addWidget(this->resolveButton);
}

void GUI::resolveIssueHandler()
{
    int i = this->getSelectedIndex();

    if (i == -1)
        return;

    Issue issue = this->issuesSorted[i];

    if (!issue.getStatus())
        return;

    std::string solverName = this->user.getName();
    this->service.updateIssue(this->service.getIssuePos(issue), solverName);
    emit issuesUpdatedSignal();
}

void GUI::listItemSelectionChangedHandler()
{
    int i = this->getSelectedIndex();

    if (i == -1)
        return;

    Issue issue = this->issuesSorted[i];

    if (issue.getStatus())
        this->resolveButton->setEnabled(true);
    else
        this->resolveButton->setEnabled(false);
}

void GUI::update()
{
    this->populateIssuesList();
}


