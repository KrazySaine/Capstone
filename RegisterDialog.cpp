#include "RegisterDialog.h"
#include "ui_RegisterDialog.h"
#include <QMessageBox>
#include <QFile>
#include <QTextStream>

RegisterDialog::RegisterDialog(std::vector<User>& usersRef, QWidget *parent)
    : QDialog(parent), ui(new Ui::RegisterDialog), users(usersRef) {
    ui->setupUi(this);
    setWindowTitle("Register");
}

RegisterDialog::~RegisterDialog() {
    delete ui;
}

void RegisterDialog::on_registerButton_clicked() {
    QString username = ui->usernameEdit->text();
    QString password = ui->passwordEdit->text();

    for (const auto& user : users) {
        if (user.username == username) {
            QMessageBox::warning(this, "Registration Failed", "Username already exists.");
            return;
        }
    }

    users.push_back({ username, password, 0.0 });
    saveUsersToFile();

    QMessageBox::information(this, "Success", "User registered successfully!");
    accept();  // Close dialog
}

void RegisterDialog::saveUsersToFile() {
    QFile file("users.txt");
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        for (const auto& user : users) {
            out << user.username << " " << user.password << " " << user.balance << "\n";
        }
        file.close();
    }
}
