#include <iostream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

// Task class definition (Base Class)
class Task {
public:
    Task(const string& description = "") : description(description), completed(false) {
        taskCount++;
    }

    Task(const Task& other) {
        this->description = other.description;
        this->completed = other.completed;
        taskCount++;
        if (this->completed) {
            completedTaskCount++;
        }
    }

    virtual ~Task() {
        if (completed) {
            completedTaskCount--;
        }
        taskCount--;
        cout << "Task '" << description << "' is being deleted.\n";
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

protected:
    string description;
    bool completed;

private:
    static int taskCount;
    static int completedTaskCount;
};

// Initialize static members
int Task::taskCount = 0;
int Task::completedTaskCount = 0;

// Derived class: PriorityTask (inherits from Task)
class PriorityTask : public Task {
public:
    PriorityTask(const string& description = "", int priority = 0) : Task(description), priority(priority) {}

    int getPriority() const {
        return priority;
    }

private:
    int priority;
};

// ToDoList class definition
class ToDoList {
public:
    // Overloaded method to add a simple task
    void addTask(const string& description) {
        Task* newTask = new Task(description);
        this->tasks.push_back(newTask);
        cout << "----------------------------------------------------------------------\n";
        cout << "Task added successfully. Total tasks: " << Task::getTaskCount() << "\n";
    }

    // Overloaded method to add a task with priority
    void addTask(const string& description, int priority) {
        PriorityTask* newTask = new PriorityTask(description, priority);
        this->tasks.push_back(newTask);
        cout << "----------------------------------------------------------------------\n";
        cout << "Priority task added successfully. Total tasks: " << Task::getTaskCount() << "\n";
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
            delete this->tasks[taskNumber - 1];
            this->tasks.erase(this->tasks.begin() + taskNumber - 1);
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

        for (size_t i = 0; i < this->tasks.size(); ++i) {
            cout << i + 1 << ". " << this->tasks[i]->getDescription() << "\n";
            cout << "   Status: " << (this->tasks[i]->isCompleted() ? "Completed" : "Incomplete") << "\n";

            // If task is a PriorityTask, show its priority
            PriorityTask* pt = dynamic_cast<PriorityTask*>(tasks[i]);
            if (pt) {
                cout << "   Priority: " << pt->getPriority() << "\n";
            }
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
        cout << "----------------------------------------------------------------------\n";
        cout << "Please choose an option:\n";
        cout << "1. Add a task\n";
        cout << "2. Add a priority task\n";
        cout << "3. Delete a task\n";
        cout << "4. View all tasks\n";
        cout << "5. Mark a task as complete\n";
        cout << "6. Exit\n";
        cout << "----------------------------------------------------------------------\n";
        cout << "Enter your choice: ";
        cin >> input;

        stringstream ss(input);
        if (!(ss >> choice) || !ss.eof()) {
            cout << "Invalid choice. Please enter a number between 1 and 6.\n";
            continue;
        }

        switch (choice) {
            case 1:
                {
                    cout << "Enter the task description: ";
                    cin.ignore();
                    string taskDescription;
                    getline(cin, taskDescription);
                    toDoList.addTask(taskDescription);
                    break;
                }
            case 2:
                {
                    cout << "Enter the task description: ";
                    cin.ignore();
                    string taskDescription;
                    getline(cin, taskDescription);
                    cout << "Enter the priority level: ";
                    int priority;
                    cin >> priority;
                    toDoList.addTask(taskDescription, priority);
                    break;
                }
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
