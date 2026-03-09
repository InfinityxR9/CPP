#include <iostream>

using namespace std;

struct Player
{
    int pid;
    int pname;
    int pscore;
    int time;
};

struct Node
{
    Player pdata;
    Node **next;
    int level;

    Node(Player p, int l) : pdata(p), level(l)
    {
        next = new Node *[level + 1];

        for (int i = 0; i < level; i++)
        {
            next[i] = nullptr;
        }
    }

    ~Node()
    {
        delete[] next;
        next = nullptr;
    }
};

class skipList
{
private:
    int MAX_LEVELS = 10;
    int curr_level;
    Node *header;

public:
    skipList()
    {
        Player sent;
        sent.pid = -1;

        curr_level = 0;
        header = new Node(sent, MAX_LEVELS);
    }

    int level_gen()
    {
        int l = 0;

        while (float(rand() / RAND_MAX) < 0.5 && l < MAX_LEVELS)
        {
            l++;
        }

        return l;
    }

    bool is_p1_greater_p2(Player p1, Player p2)
    {
        if (p1.pscore != p2.pscore)
        {
            return p1.pscore > p2.pscore;
        }

        return p1.time < p2.time;
    }

    Node *searchPlayer(int id)
    {
        Node *curr = header->next[0];
        while (curr != nullptr)
        {
            if (curr->pdata.pid == id)
            {
                return curr;
            }
            curr = curr->next[0];
        }

        return nullptr;
    }

    void insertPlayer(Player p)
    {
        Node *update[MAX_LEVELS + 1];
        Node *curr = header;
        Node *nextptr;

        for (int i = curr_level; i >= 0; i--)
        {
            nextptr = curr->next[i];

            while (nextptr != nullptr && is_p1_greater_p2(nextptr->pdata, p))
            {
                curr = nextptr;
            }
            update[i] = curr;
        }

        int lvl = level_gen();

        if (lvl > curr_level)
        {
            for (int i = curr_level + 1; i < lvl; i++)
            {
                update[i] = header;
            }
            curr_level = lvl;
        }

        Node *new_node = new Node(p, lvl);

        for (int i = 0; i <= lvl; i++)
        {
            new_node->next[i] = update[i]->next[i];
            update[i]->next[i] = new_node;
        }
    }

    void deletePlayer(int id)
    {
        Node *update[MAX_LEVELS + 1];
        Node *curr = header;

        Node *tar = header->next[0];
        while (tar != nullptr && tar->pdata.pid != id)
        {
            tar = tar->next[0];
        }

        if (tar == nullptr)
            return;

        for (int i = curr_level; i >= 0; i--)
        {
            while (curr->next[i] != nullptr && is_p1_greater_p2(curr->next[i]->pdata, tar->pdata))
            {
                curr = curr->next[i];
            }
            update[i] = curr;
        }

        for (int i = 0; i <= curr_level; i++)
        {
            if (update[i]->next[i] != tar)
            {
                break;
            }
            update[i]->next[i] = tar->next[i];
        }

        delete tar;

        while (curr_level > 0 && header->next[curr_level] == nullptr)
        {
            curr_level--;
        }
    }
}

int main()
{
    cout << "Hello world" << endl;

    return 0;
}