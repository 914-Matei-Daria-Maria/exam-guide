#pragma once

#include <QWidget>
#include <QHBoxLayout>
#include <QListWidget>
#include <QPushButton>
#include <QLineEdit>
#include "../Service/Service.h"

class GUI: public QWidget, public Observer
{
        Q_OBJECT
private:
    Service &service;
    User user;
    std::vector<Issue> issuesSorted;

    QVBoxLayout *mainLayout;
    QListWidget *issuesList;
    QLineEdit* addEdit;
    QPushButton* addButton;
    QPushButton* removeButton;
    QPushButton* resolveButton;

    void createIssuesList();
    void populateIssuesList();
    void createAddIssue();
    void connectSignalsAndSlots();
    void createRemoveIssue();
    int getSelectedIndex();
    void createResolveIssue();

public:
    GUI(Service &service, User& user);
    void update() override;

public slots:
    void addIssueHandler();
    void removeIssueHandler();
    void resolveIssueHandler();
    void listItemSelectionChangedHandler();

signals:
    void issuesUpdatedSignal();
};