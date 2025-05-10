#include "UserDashboard.h"
#include "ui_UserDashboard.h"
#include <QMessageBox>
#include <QInputDialog>
#include <QFile>
#include <QTextStream>

UserDashboard::UserDashboard(std::vector<User>& usersRef, int userIndex, QWidget *parent)
    : QWidget(parent), ui(new Ui::UserDashboard), users(usersRef), currentUserIndex(userIndex) {
    ui->setupUi(this);
    setWindowTitle("User Dashboard - " + users[userIndex].username);
}

UserDashboard::~UserDashboard() {
    delete ui;
}

void UserDashboard::saveUsersToFile() {
    QFile file("users.txt");
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        for (const auto& user : users) {
            out << user.username << " " << user.password << " " << user.balance << "\n";
        }
        file.close();
    }
}

void UserDashboard::on_checkBalanceButton_clicked() {
    double balance = users[currentUserIndex].balance;
    QMessageBox::information(this, "Balance", "Your current balance is $" + QString::number(balance, 'f', 2));
}

void UserDashboard::on_depositButton_clicked() {
    double amount = QInputDialog::getDouble(this, "Deposit", "Enter amount to deposit:", 0, 0);
    if (amount > 0) {
        users[currentUserIndex].balance += amount;
        saveUsersToFile();
        QMessageBox::information(this, "Success", "Deposited successfully.");
    } else {
        QMessageBox::warning(this, "Error", "Invalid amount.");
    }
}

void UserDashboard::on_withdrawButton_clicked() {
    double amount = QInputDialog::getDouble(this, "Withdraw", "Enter amount to withdraw:", 0, 0);
    if (amount > 0 && users[currentUserIndex].balance >= amount) {
        users[currentUserIndex].balance -= amount;
        saveUsersToFile();
        QMessageBox::information(this, "Success", "Withdrawn successfully.");
    } else {
        QMessageBox::warning(this, "Error", "Invalid amount or insufficient balance.");
    }
}

void UserDashboard::on_transferButton_clicked() {
    QString recipient = QInputDialog::getText(this, "Transfer", "Enter recipient username:");
    double amount = QInputDialog::getDouble(this, "Amount", "Enter amount to transfer:", 0, 0);
    if (amount <= 0 || amount > users[currentUserIndex].balance) {
        QMessageBox::warning(this, "Error", "Invalid amount or insufficient balance.");
        return;
    }

    int recipientIndex = -1;
    for (int i = 0; i < users.size(); ++i) {
        if (users[i].username == recipient) {
            recipientIndex = i;
            break;
        }
    }

    if (recipientIndex == -1) {
        QMessageBox::warning(this, "Error", "Recipient not found.");
    } else {
        users[currentUserIndex].balance -= amount;
        users[recipientIndex].balance += amount;
        saveUsersToFile();
        QMessageBox::information(this, "Success", "Transfer successful.");
    }
}
