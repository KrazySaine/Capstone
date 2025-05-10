#ifndef USERDASHBOARD_H
#define USERDASHBOARD_H

#include <QWidget>
#include <vector>

struct User {
    QString username;
    QString password;
    double balance;
};

namespace Ui {
class UserDashboard;
}

class UserDashboard : public QWidget {
    Q_OBJECT

public:
    explicit UserDashboard(std::vector<User>& usersRef, int userIndex, QWidget *parent = nullptr);
    ~UserDashboard();

private slots:
    void on_checkBalanceButton_clicked();
    void on_depositButton_clicked();
    void on_withdrawButton_clicked();
    void on_transferButton_clicked();

private:
    Ui::UserDashboard *ui;
    std::vector<User>& users;
    int currentUserIndex;

    void saveUsersToFile();
};

#endif // USERDASHBOARD_H
