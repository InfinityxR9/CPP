#include <iostream>

using namespace std;

/**
 * `Player` structure
 * @param pid Id of Player
 * @param pname Name of Player
 * @param pscore Score of Player
 * @param time Timestamp of Player
 */
struct Player
{
    int pid;
    int pname;
    int pscore;
    int time;
};

/**
 * `Node` structure of Skip List
 * @param pdata The `Player` object storing Player's data
 * @param next Array of Pointers to next `Node` in each level
 * @param level The level of that `Node` (Counted from 0)
 */
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

/**
 * Skip List Class
 * 
 * @param MAX_LEVELS Maximum levels in Skip List 
 * @param curr_level Current total number of levels in Skip List
 * @param header Sentinel Header node storing pointer to first Node in each Level
 */
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

    /**
     * Generate to which level a new Node would go in Skip list
     * @returns Level of new Node
     */
    int level_gen()
    {
        int l = 0;

        while (float(rand() / RAND_MAX) < 0.5 && l < MAX_LEVELS)
        {
            l++;
        }

        return l;
    }

    /**
     * Check whether rank of `p1` would be greater that `p2` based on score and timestamp values
     * @param p1 Player 1 structure
     * @param p2 Player 2 structure
     * @returns True if Player 1 would be ranked higher than Player 2
     */
    bool is_p1_greater_p2(Player p1, Player p2)
    {
        if (p1.pscore != p2.pscore)
        {
            return p1.pscore > p2.pscore;
        }

        return p1.time < p2.time;
    }

    /**
     * Searches a player using Player's ID
     * @param id ID of player
     * @returns Pointer to the node whose ID is `id`
     * @note Since Player ID is unique, searching is done using the ID attribute
     */
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

    /**
     * Inserts a new player into the skip list
     * @param p `Player` structure of new player `p` to be inserted into the skip list
     */
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

    /**
     * Delete the player with given Player ID
     * @param id ID of player to be deleted
     */
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
        tar = nullptr;

        while (curr_level > 0 && header->next[curr_level] == nullptr)
        {
            curr_level--;
        }
    }

    /**
     * Function to update score of player with ID `id` with score `score`
     * @param id ID of player whose score is to be updated
     * @param score New Score of Player
     * @note This algorithm follows by searching the player with given id, constructing a copy Node with old player structure and new score, Deleting the old Node and inserting the new Node
     */
    void updateScore(int id, int score)
    {
        Node *p = searchPlayer(id);
        if (p == nullptr)
            return;

        Player temp = p->pdata;
        deletePlayer(id);

        temp.pscore = score;

        insertPlayer(temp);
    }

    /**
     * Function to get rank of the Player with ID `id`
     * @returns Rank of Player, if it exists, otherwise -1
     */
    int getRank(int id)
    {
        Node *curr = header->next[0];
        int rank = 1;

        while (curr != nullptr && curr->pdata.pid != id)
        {
            rank++;
            curr = curr->next[0];
        }

        return rank ? curr != nullptr : -1;
    }

    /**
     * Display the Top `k` Players in the Leaderboard
     */
    void getTopK(int k)
    {
        Node *curr = header->next[0];
        int count = 0;

        while (curr != nullptr && count < k)
        {
            cout << curr->pdata.pid << " " << pdata.pname << " " << curr->pdata.pscore << endl;
            curr = curr->next[0];
            count++;
        }
    }

    /**
     * Display the current Leaderboard with rank
     */
    void displayLeaderboard()
    {
        Node *curr = header->next[0];
        int rank = 1;

        while (curr != nullptr)
        {
            cout << rank << curr->pdata.pid << " " << pdata.pname << " " << curr->pdata.pscore << endl;
            curr = curr->next[0];
            rank++;
        }
    }

    /**
     * Display the entire Skip List structure with Level and Score of Player, sorted by rank in descending order
     */
    void displaySkipListStructure()
    {
        for (int i = curr_level; i >= 0; i--)
        {
            Node *n = header->next[i];
            cout << "Level " << i << ":";

            while (n != nullptr)
            {
                cout << n->pdata.pscore << " ";
                n = n->next[i];
            }
            cout << endl;
        }
    }
}

int main()
{
    cout << "Hello world" << endl;

    return 0;
}