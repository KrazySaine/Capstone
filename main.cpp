#include "mainwindow.h"
#include <QApplication>
#include <QPushButton>
#include <QMessageBox>
#include <vector>
#include <QFile>
#include <QTextStream>

#include "RegisterDialog.h"
#include "LoginDialog.h"
#include "AdminPanel.h"
#include "UserDashboard.h"

// Shared user data
std::vector<User> users;

void loadUsers() {
    users.clear();
    QFile file("users.txt");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        while (!in.atEnd()) {
            QString username, password;
            double balance;
            in >> username >> password >> balance;
            if (!username.isEmpty()) {
                users.push_back({ username, password, balance });
            }
        }
        file.close();
    }
}

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    loadUsers();

    while (true) {
        QStringList options = { "Login", "Register", "Exit" };
        bool ok;
        QString choice = QInputDialog::getItem(nullptr, "Cane Family Bank", "Choose an option:", options, 0, false, &ok);

        if (!ok || choice == "Exit") {
            break;
        } else if (choice == "Register") {
            RegisterDialog registerDialog(users);
            registerDialog.exec();
        } else if (choice == "Login") {
            LoginDialog loginDialog(users);
            if (loginDialog.exec() == QDialog::Accepted) {
                if (loginDialog.isAdminLoggedIn()) {
                    AdminPanel *admin = new AdminPanel(users);
                    admin->show();
                    app.exec();  // Launch admin panel loop
                } else {
                    int userIdx = loginDialog.getLoggedInUserIndex();
                    if (userIdx >= 0) {
                        UserDashboard *dashboard = new UserDashboard(users, userIdx);
                        dashboard->show();
                        app.exec();  // Launch user dashboard loop
                    }
                }
            }
        }
    }

    return 0;
}

