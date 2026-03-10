#include <iostream>

using namespace std;

/**
 * Message Node Structure as Doubly Linked List
 * @param msgId Message ID
 * @param senderId Sender ID
 * @param txt Text of the message
 * @param time Timestamp noted (Noted in Seconds)
 * @param isDeleted Flag whether message is deleted for me
 * @param isDeletedForEveryone Flag whether message is deleted for everyone
 * @param next Pointer to next Node
 * @param prev Pointer to previous Node
 */
struct Msg
{
    int msgId;
    int senderId;
    string txt;
    int time;
    bool isDeleted;
    bool isDeletedForEveryone;

    Msg *next;
    Msg *prev;

    Msg(int id, int sId, string &msg, int t) : msgId(id), senderId(sId), txt(msg), time(t)
    {
        isDeleted = isDeletedForEveryone = false;
        next = prev = nullptr;
    }
};

/**
 * Stack Node Structure
 * @param data Pointer to Corresponding Message Node
 * @param next Pointer to next Node
 */
struct Node
{
    Msg *data;
    Node *next;
};

/**
 * Stack Class using Singly Linked List, used to store the Deleted Messages
 */
class Stack
{
    Node *head;

public:
    Stack()
    {
        head = nullptr;
    }

    /**
     * Push Operation stack
     * @param key Pointer to the Message Node to be pushed
     */
    void push(Msg *key)
    {
        Node *n = new Node;
        n->data = key;
        n->next = head;
        head = n;
    }

    /**
     * Pop Operation stack
     * @returns Pointer to the Latest Deleted Message Node
     */
    Msg *pop()
    {
        if (head == nullptr)
            return nullptr;

        Node *temp = head;
        Msg *data = head->data;
        head = head->next;
        delete temp;
        temp = nullptr;
        return data;
    }

    /**
     * Utility Function to get whether stack is empty or not
     * @returns `true` if stack is empty, otherwise `false`
     */
    bool isEmpty()
    {
        return (head == nullptr);
    }

    /**
     * Destructor to free up all nodes
     */
    ~Stack()
    {
        Node *curr = head;
        while (curr != nullptr)
        {
            Node *temp = curr;
            curr = curr->next;
            delete temp;
        }

        head = nullptr;
    }
};

/**
 * Chat Message System Class using Doubly Linked List
 * @note The `head` pointer points to the oldest message, while new messages are inserted at `tail` pointer
 */
class Messager
{
private:
    Msg *head;
    Msg *tail;
    Stack deleted;

public:
    Messager()
    {
        head = tail = nullptr;
    }

    /**
     * Finds the Message Node from Message ID `id`
     * @param id Message ID
     * @returns Pointer to Message Node if found
     */
    Msg *findMsg(int id)
    {
        Msg *temp = head;
        while (temp != nullptr)
        {
            if (temp->msgId == id)
                return temp;
            temp = temp->next;
        }
        return nullptr;
    }

    /**
     * Send New message to Chat
     * @param id Message ID
     * @param sender Sender ID
     * @param text Text String sent
     * @param time Timestamp noted
     * @note This Algorithm works by inserting the new node at tail of the DLL
     */
    void sendMessage(int id, int sender, string &text, int time)
    {
        Msg *n = new Msg(id, sender, text, time);
        if (head == nullptr)
        {
            head = tail = n;
            return;
        }

        tail->next = n;
        n->prev = tail;
        tail = n;
    }

    /**
     * Marks the message as 'Deleted for Everyone'
     * @param id Message ID of message to be marked
     * @param curr_time Current time to check deleting constraint (Difference of timestamp should be <= 120 seconds)
     */
    void deleteForEveryone(int id, int curr_time)
    {
        Msg *msg = findMsg(id);
        if (msg == nullptr)
        {
            return;
        }

        if (curr_time - msg->time <= 120 && !msg->isDeleted && !msg->isDeletedForEveryone)
        {
            msg->isDeletedForEveryone = true;
            deleted.push(msg);
        }
    }

    /**
     * Marks the message as 'Deleted for Me'
     * @param id Message ID of message to be marked
     */
    void deleteForMe(int id)
    {
        Msg *msg = findMsg(id);
        if (msg == nullptr || msg->isDeletedForEveryone || msg->isDeleted)
        {
            return;
        }
        msg->isDeleted = true;
        deleted.push(msg);
    }

    /**
     * Restores the last deleted message
     * @note This algorithm works by Popping from the `deleted` stack and marking the message as not deleted
     */
    void undoLastDelete()
    {
        if (deleted.isEmpty())
            return;

        Msg *popped = deleted.pop();
        if (popped->isDeleted)
        {
            popped->isDeleted = false;
        }
        else
        {
            popped->isDeletedForEveryone = false;
        }
    }

    /**
     * Display Entire Chat History
     * @note Text Message is shown only if it is "deleted for everyone", and is skiped if message is "deleted for me"
     */
    void displayChat()
    {
        Msg *temp = head;
        while (temp != nullptr)
        {
            if (temp->isDeletedForEveryone)
            {
                cout << "This message was deleted" << endl;
            }
            else if (!temp->isDeleted)
            {
                cout << temp->senderId << " " << temp->txt << endl;
            }

            temp = temp->next;
        }
    }

    /**
     * Destructor to free up all nodes
     */
    ~Messager()
    {
        Msg *curr = head;
        while (curr != nullptr)
        {
            Msg *temp = curr;
            curr = curr->next;
            delete temp;
        }

        head = tail = nullptr;
    }
};

int main()
{
    // Test Case 1
    Messager chat;

    cout << "Sending Messages\n";

    chat.sendMessage(1, 101, "Hello", 10);
    chat.sendMessage(2, 102, "Hi", 20);
    chat.sendMessage(3, 103, "How are you?", 30);

    chat.displayChat();

    cout << "\nDelete Message 2 for everyone\n";
    chat.deleteForEveryone(2, 100);
    chat.displayChat();

    cout << "\nDelete Message 3 for me\n";
    chat.deleteForMe(3);
    chat.displayChat();

    cout << "\nUndo last delete\n";
    chat.undoLastDelete();
    chat.displayChat();

    cout << "\nUndo again\n";
    chat.undoLastDelete();
    chat.displayChat();

    cout << "\nAttempt delete after time limit\n";
    chat.deleteForEveryone(1, 500);
    chat.displayChat();

    // Test Case 2
    Messager chat2;

    cout << "Sending Messages\n";

    chat2.sendMessage(1, 101, "Hello everyone", 10);
    chat2.sendMessage(2, 102, "Hi!", 20);
    chat2.sendMessage(3, 103, "How are you all?", 30);
    chat2.sendMessage(4, 104, "I'm good", 40);
    chat2.sendMessage(5, 101, "Nice to hear that", 50);
    chat2.sendMessage(6, 102, "What are you doing?", 60);
    chat2.sendMessage(7, 103, "Working on assignment", 70);
    chat2.sendMessage(8, 104, "Same here", 80);

    cout << "\nInitial Chat\n";
    chat2.displayChat();

    cout << "\nDelete message 3 for everyone\n";
    chat2.deleteForEveryone(3, 100);
    chat2.displayChat();

    cout << "\nDelete message 6 for me\n";
    chat2.deleteForMe(6);
    chat2.displayChat();

    cout << "\nDelete message 7 for everyone\n";
    chat2.deleteForEveryone(7, 150);
    chat2.displayChat();

    cout << "\nUndo last delete\n";
    chat2.undoLastDelete();
    chat2.displayChat();

    cout << "\nUndo again\n";
    chat2.undoLastDelete();
    chat2.displayChat();

    cout << "\nAttempt delete after time limit (message 1)\n";
    chat2.deleteForEveryone(1, 400);
    chat2.displayChat();

    cout << "\nDelete message 8 for me\n";
    chat2.deleteForMe(8);
    chat2.displayChat();

    cout << "\nUndo last delete\n";
    chat2.undoLastDelete();
    chat2.displayChat();

    return 0;
}