#include "LoginDialog.h"
#include "ui_LoginDialog.h"
#include <QMessageBox>

LoginDialog::LoginDialog(std::vector<User>& usersRef, QWidget *parent)
    : QDialog(parent), ui(new Ui::LoginDialog), users(usersRef) {
    ui->setupUi(this);
    setWindowTitle("Login");
}

LoginDialog::~LoginDialog() {
    delete ui;
}

void LoginDialog::on_loginButton_clicked() {
    QString username = ui->usernameEdit->text();
    QString password = ui->passwordEdit->text();

    if (username == "admin" && password == "admin123") {
        adminLoggedIn = true;
        accept(); // Close dialog
        return;
    }

    for (int i = 0; i < users.size(); ++i) {
        if (users[i].username == username && users[i].password == password) {
            loggedInIndex = i;
            accept();
            return;
        }
    }

    QMessageBox::warning(this, "Login Failed", "Invalid credentials.");
}

int LoginDialog::getLoggedInUserIndex() const {
    return loggedInIndex;
}

bool LoginDialog::isAdminLoggedIn() const {
    return adminLoggedIn;
}
