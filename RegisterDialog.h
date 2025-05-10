#ifndef REGISTERDIALOG_H
#define REGISTERDIALOG_H

#include <QDialog>
#include <vector>

struct User {
    QString username;
    QString password;
    double balance;
};

namespace Ui {
class RegisterDialog;
}

class RegisterDialog : public QDialog {
    Q_OBJECT

public:
    explicit RegisterDialog(std::vector<User>& usersRef, QWidget *parent = nullptr);
    ~RegisterDialog();

private slots:
    void on_registerButton_clicked();

private:
    Ui::RegisterDialog *ui;
    std::vector<User>& users;

    void saveUsersToFile();
};

#endif // REGISTERDIALOG_H
