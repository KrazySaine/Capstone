#include "AdminPanel.h"
#include "ui_AdminPanel.h"
#include <QMessageBox>
#include <QInputDialog>
#include <QFile>
#include <QTextStream>

AdminPanel::AdminPanel(std::vector<User>& usersRef, QWidget *parent)
    : QWidget(parent), ui(new Ui::AdminPanel), users(usersRef) {
    ui->setupUi(this);
    setWindowTitle("Admin Panel");
    loadUserList();
}

AdminPanel::~AdminPanel() {
    delete ui;
}

void AdminPanel::loadUserList() {
    ui->userListWidget->clear();
    for (const auto& u : users) {
        ui->userListWidget->addItem(u.username + " | $" + QString::number(u.balance, 'f', 2));
    }
}

void AdminPanel::saveUsersToFile() {
    QFile file("users.txt");
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        for (const auto& user : users) {
            out << user.username << " " << user.password << " " << user.balance << "\n";
        }
        file.close();
    }
}

void AdminPanel::on_searchButton_clicked() {
    QString username = QInputDialog::getText(this, "Search User", "Enter username:");
    for (const auto& u : users) {
        if (u.username == username) {
            QMessageBox::information(this, "User Found", "Username: " + u.username + "\nBalance: $" + QString::number(u.balance));
            return;
        }
    }
    QMessageBox::warning(this, "Not Found", "User not found.");
}

void AdminPanel::on_deleteButton_clicked() {
    QString username = QInputDialog::getText(this, "Delete User", "Enter username:");
    for (int i = 0; i < users.size(); ++i) {
        if (users[i].username == username) {
            users.erase(users.begin() + i);
            saveUsersToFile();
            loadUserList();
            QMessageBox::information(this, "Deleted", "User deleted.");
            return;
        }
    }
    QMessageBox::warning(this, "Not Found", "User not found.");
}

void AdminPanel::on_addFundsButton_clicked() {
    QString username = QInputDialog::getText(this, "Add Funds", "Enter username:");
    double amount = QInputDialog::getDouble(this, "Amount", "Enter amount:");

    for (auto& u : users) {
        if (u.username == username) {
            u.balance += amount;
            saveUsersToFile();
            loadUserList();
            QMessageBox::information(this, "Success", "Funds added.");
            return;
        }
    }
    QMessageBox::warning(this, "Not Found", "User not found.");
}

void AdminPanel::on_resetPasswordButton_clicked() {
    QString username = QInputDialog::getText(this, "Reset Password", "Enter username:");
    QString newPass = QInputDialog::getText(this, "New Password", "Enter new password:");

    for (auto& u : users) {
        if (u.username == username) {
            u.password = newPass;
            saveUsersToFile();
            QMessageBox::information(this, "Success", "Password reset.");
            return;
        }
    }
    QMessageBox::warning(this, "Not Found", "User not found.");
}

void AdminPanel::on_summaryButton_clicked() {
    double total = 0;
    for (const auto& u : users) total += u.balance;
    QMessageBox::information(this, "System Summary",
                             "Total Users: " + QString::number(users.size()) +
                                 "\nTotal Funds: $" + QString::number(total, 'f', 2));
}
