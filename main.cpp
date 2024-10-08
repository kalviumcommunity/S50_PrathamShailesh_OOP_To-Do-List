#include <iostream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

// Base class (parent class)
class BasicTask {
public:
    BasicTask(const string& description = "") : description(description) {}
    
    // Getter for description
    string getDescription() const {
        return description;
    }

protected:
    string description; 
};

// Derived class (child of BasicTask) - Single Inheritance
class Task : public BasicTask {
public:
    // Task constructor (inheriting from BasicTask)
    Task(const string& description = "") : BasicTask(description), completed(false) {
        taskCount++;
    }

    // Copy constructor
    Task(const Task& other) : BasicTask(other.description) {
        this->completed = other.completed;
        taskCount++;
        if (this->completed) {
            completedTaskCount++;
        }
    }

    // Destructor
    ~Task() {
        if (completed) {
            completedTaskCount--;
        }
        taskCount--;
        cout << "Task '" << description << "' is being deleted.\n";
    }

    // Mark the task as complete
    void markAsComplete() {
        if (!this->completed) {
            this->completed = true;
            completedTaskCount++;
        }
    }

    // Check if task is completed
    bool isCompleted() const {
        return completed;
    }

    // Static methods for task counts
    static int getTaskCount() {
        return taskCount;
    }

    static int getCompletedTaskCount() {
        return completedTaskCount;
    }

protected:
    bool completed;

private:
    static int taskCount;
    static int completedTaskCount;
};

// Initialize static variables
int Task::taskCount = 0;
int Task::completedTaskCount = 0;

// Derived class (child of Task) - Multi-level inheritance
class PriorityTask : public Task {
public:
    PriorityTask(const string& description = "", int priority = 1) : Task(description), priority(priority) {}

    // Set task priority
    void setPriority(int priorityLevel) {
        priority = priorityLevel;
    }

    // Get task priority
    int getPriority() const {
        return priority;
    }

private:
    int priority;
};

// ToDoList class managing tasks
class ToDoList {
public:
    void showMenu() const {
        cout << "----------------------------------------------------------------------\n";
        cout << "Please choose an option:\n";
        cout << "1. Add a task\n";
        cout << "2. Add a priority task\n";
        cout << "3. Delete a task\n";
        cout << "4. View all tasks\n";
        cout << "5. Mark a task as complete\n";
        cout << "6. Exit\n";
    }

    void addTask() {
        cout << "Enter the task: ";
        string taskDescription;
        cin.ignore();
        getline(cin, taskDescription);
        Task* newTask = new Task(taskDescription);
        tasks.push_back(newTask);
        cout << "Task added successfully. Total tasks: " << Task::getTaskCount() << "\n";
    }

    void addPriorityTask() {
        cout << "Enter the task: ";
        string taskDescription;
        cin.ignore();
        getline(cin, taskDescription);
        cout << "Enter task priority (1 = High, 2 = Medium, 3 = Low): ";
        int priorityLevel;
        cin >> priorityLevel;
        PriorityTask* newPriorityTask = new PriorityTask(taskDescription, priorityLevel);
        tasks.push_back(newPriorityTask);
        cout << "Priority task added successfully with priority " << priorityLevel << ". Total tasks: " << Task::getTaskCount() << "\n";
    }

    void deleteTask() {
        if (tasks.empty()) {
            cout << "No tasks available to delete.\n";
            return;
        }

        cout << "Enter the task number to delete: ";
        int taskNumber;
        cin >> taskNumber;

        if (taskNumber < 1 || taskNumber > tasks.size()) {
            cout << "Invalid task number.\n";
        } else {
            delete tasks[taskNumber - 1];
            tasks.erase(tasks.begin() + taskNumber - 1);
            Task::getTaskCount();
            cout << "Task deleted successfully. Total tasks: " << Task::getTaskCount() << "\n";
        }
    }

    void viewTasks() const {
        if (tasks.empty()) {
            cout << "No tasks available.\n";
            return;
        }
        for (size_t i = 0; i < tasks.size(); ++i) {
            cout << i + 1 << ". " << tasks[i]->getDescription() << " - " << (tasks[i]->isCompleted() ? "Completed" : "Incomplete") << '\n';

            PriorityTask* pt = dynamic_cast<PriorityTask*>(tasks[i]);
            if (pt) {
                cout << "   Priority: " << pt->getPriority() << "\n";
            }
        }
        cout << "Total completed tasks: " << Task::getCompletedTaskCount() << "\n";
    }

    void markTaskAsComplete() {
        if (tasks.empty()) {
            cout << "No tasks available to mark as complete.\n";
            return;
        }

        viewTasks();
        cout << "Enter the task number to mark as complete: ";
        int taskNumber;
        cin >> taskNumber;

        if (taskNumber < 1 || taskNumber > tasks.size()) {
            cout << "Invalid task number.\n";
        } else {
            tasks[taskNumber - 1]->markAsComplete();
            cout << "Task marked as complete successfully.\n";
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

// Main function to run the program
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
            cout << "Invalid choice. Please enter a number between 1 and 6.\n";
            continue;
        }

        switch (choice) {
            case 1:
                toDoList.addTask();
                break;
            case 2:
                toDoList.addPriorityTask();
                break;
            case 3:
                toDoList.deleteTask();
                break;
            case 4:
                toDoList.viewTasks();
                break;
            case 5:
                toDoList.markTaskAsComplete();
                break;
            case 6:
                cout << "Exiting the program.\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 6);

    return 0;
}
