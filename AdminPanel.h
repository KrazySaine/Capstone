#ifndef ADMINPANEL_H
#define ADMINPANEL_H

#include <QWidget>
#include <vector>

struct User {
    QString username;
    QString password;
    double balance;
};

namespace Ui {
class AdminPanel;
}

class AdminPanel : public QWidget {
    Q_OBJECT

public:
    explicit AdminPanel(std::vector<User>& usersRef, QWidget *parent = nullptr);
    ~AdminPanel();

private slots:
    void loadUserList();
    void on_searchButton_clicked();
    void on_deleteButton_clicked();
    void on_addFundsButton_clicked();
    void on_resetPasswordButton_clicked();
    void on_summaryButton_clicked();

private:
    Ui::AdminPanel *ui;
    std::vector<User>& users;

    void saveUsersToFile();
};

#endif // ADMINPANEL_H
