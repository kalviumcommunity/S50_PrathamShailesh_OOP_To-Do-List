#include <iostream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

class Task {
public:
    Task(const string& description = "") : description(description), completed(false) {
        taskCount++;
    }

    string getDescription() const {
        return this->description; 
    }

    bool isCompleted() const {
        return this->completed; 
    }

    void markAsComplete() {
        if (!this->completed) {
            this->completed = true;
            completedTaskCount++;
        }
    }

    static int getTaskCount() {
        return taskCount;
    }

    static int getCompletedTaskCount() {
        return completedTaskCount;
    }

    static void decrementTaskCount() {
        if (taskCount > 0) {
            --taskCount;
        }
    }

    static void decrementCompletedTaskCount() {
        if (completedTaskCount > 0) {
            --completedTaskCount;
        }
    }

private:
    string description;
    bool completed;
    static int taskCount;
    static int completedTaskCount;  
};

int Task::taskCount = 0;
int Task::completedTaskCount = 0;

class ToDoList {
public:

    void showMenu() const {
        cout << "----------------------------------------------------------------------\n";
        cout << "Please choose an option:\n";
        cout << "1. Add a task\n";
        cout << "2. Delete a task\n";
        cout << "3. View all tasks\n";
        cout << "4. Mark a task as complete\n";
        cout << "5. Exit\n";
    }

    void addTask() {
        cout << "Enter the task: ";
        string taskDescription;
        cin.ignore();
        getline(cin, taskDescription);
        Task* newTask = new Task(taskDescription); 
        this->tasks.push_back(newTask);
        cout << "----------------------------------------------------------------------\n";
        cout << "Task added successfully. Total tasks: " << Task::getTaskCount() << "\n";
    }

    void deleteTask() {
        cout << "----------------------------------------------------------------------\n";
        if (this->tasks.empty()) { 
            cout << "No tasks available to delete.\n";
            return;
        }

        cout << "Enter the task number to delete: ";
        int taskNumber;
        cin >> taskNumber;

        if (taskNumber < 1 || taskNumber > this->tasks.size()) { 
            cout << "Invalid task number.\n";
        } else {
            if (this->tasks[taskNumber - 1]->isCompleted()) {
                Task::decrementCompletedTaskCount();
            }
            delete this->tasks[taskNumber - 1];
            this->tasks.erase(this->tasks.begin() + taskNumber - 1); 
            Task::decrementTaskCount();
            cout << "Task deleted successfully.\n";
            cout << "Total tasks remaining: " << Task::getTaskCount() << "\n";
        }
    }

    void viewTasks() const {
        cout << "----------------------------------------------------------------------\n";
        if (this->tasks.empty()) { 
            cout << "No tasks available.\n";
            return;
        }
        cout << "Tasks:\n";
        for (size_t i = 0; i < this->tasks.size(); ++i) { 
            cout << i + 1 << ". " << this->tasks[i]->getDescription() << "\n"; 
            cout << "Status: " << (this->tasks[i]->isCompleted() ? "Completed" : "Incomplete") << '\n'; 
        }
        cout << "----------------------------------------------------------------------\n";
        cout << "Total completed tasks: " << Task::getCompletedTaskCount() << "\n";  
    }

    void markTaskAsComplete() {
        cout << "----------------------------------------------------------------------\n";
        if (this->tasks.empty()) { 
            cout << "No tasks available to mark as complete.\n";
            return;
        }

        this->viewTasks(); 
        cout << "Enter the task number to mark as complete: ";
        int taskNumber;
        cin >> taskNumber;

        if (taskNumber < 1 || taskNumber > this->tasks.size()) { 
            cout << "Invalid task number.\n";
        } else {
            this->tasks[taskNumber - 1]->markAsComplete(); 
            cout << "----------------------------------------------------------------------\n";
            cout << "Task marked as complete successfully.\n";
            cout << "Total completed tasks: " << Task::getCompletedTaskCount() << "\n"; 
        }
    }

    ~ToDoList() {
        for (Task* task : tasks) {
            delete task;
        }
    }

private:
    vector<Task*> tasks;
};

int main() {
    ToDoList toDoList;
    int choice;
    string input;
    cout << "----------------------------------------------------------------------\n";
    cout << "Welcome to your To-Do List Manager!\n";

    do {
        toDoList.showMenu();
        cout << "Enter your choice: ";
        cin >> input;

        stringstream ss(input);
        if (!(ss >> choice) || !ss.eof()) {
            cout << "Invalid choice. Please enter a number between 1 and 5.\n";
            continue;
        }

        switch (choice) {
            case 1:
                toDoList.addTask();
                break;
            case 2:
                toDoList.deleteTask();
                break;
            case 3:
                toDoList.viewTasks();
                break;
            case 4:
                toDoList.markTaskAsComplete();
                break;
            case 5:
                cout << "Exiting the program.\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 5);

    return 0;
}
