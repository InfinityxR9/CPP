#include <iostream>
#include <cstdlib>
#include <ctime>

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
    string pname;
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

        for (int i = 0; i <= level; i++)
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
class SkipList
{
private:
    int MAX_LEVELS = 10;
    int curr_level;
    Node *header;

public:
    SkipList()
    {
        Player sent{-1, "", 0, 0};

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

        while ((float)rand() / RAND_MAX < 0.5 && l < MAX_LEVELS)
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
    bool is_p1_greater_p2(const Player &p1, const Player &p2)
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
                nextptr = curr->next[i];
            }
            update[i] = curr;
        }

        int lvl = level_gen();

        if (lvl > curr_level)
        {
            for (int i = curr_level + 1; i <= lvl; i++)
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

        return curr != nullptr ? rank : -1;
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
            cout << curr->pdata.pid << " " << curr->pdata.pname << " " << curr->pdata.pscore << endl;
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
            cout << rank << " " << curr->pdata.pid << " " << curr->pdata.pname << " " << curr->pdata.pscore << " " << curr->pdata.time << endl;
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

    ~SkipList()
    {
        Node *curr = header->next[0];
        while (curr != nullptr)
        {
            Node *temp = curr;
            curr = curr->next[0];
            delete temp;
            temp = nullptr;
        }

        delete header;
        header = nullptr;
    }
};

int main()
{
    srand(time(NULL));
    SkipList l;

    Player p1{101, "Aryan", 950, 10};
    Player p2{102, "Aditya", 870, 20};
    Player p3{103, "Daksh", 920, 30};
    Player p4{104, "Pranjal", 870, 15};
    Player p5{105, "Farhan", 990, 25};

    cout << "Inserting Players" << endl;
    l.insertPlayer(p1);
    l.insertPlayer(p2);
    l.insertPlayer(p3);
    l.insertPlayer(p4);
    l.insertPlayer(p5);

    cout << "\nLeaderboard after insertion:\n";
    l.displayLeaderboard();

    cout << "\nSkip List Structure:\n";
    l.displaySkipListStructure();

    cout << "\nSearching Player with ID 103:\n";
    Node *found = l.searchPlayer(103);

    if (found != nullptr)
        cout << "Player Found. Score = " << found->pdata.pscore << " Name= " << found->pdata.pname << endl;
    else
        cout << "Player not found\n";

    cout << "\nRank of Player 103: ";
    cout << l.getRank(103) << endl;

    cout << "\nUpdating score of Player 102 to 980\n";
    l.updateScore(102, 980);

    cout << "\nLeaderboard after score update:\n";
    l.displayLeaderboard();

    cout << "\nSkip List Structure:\n";
    l.displaySkipListStructure();

    cout << "\nDeleting Player 104\n";
    l.deletePlayer(104);

    cout << "\nLeaderboard after deletion:\n";
    l.displayLeaderboard();

    cout << "\nTop 3 Players:\n";
    l.getTopK(3);

    cout << "\nFinal Skip List Structure:\n";
    l.displaySkipListStructure();

    // Test Case 2
    cout << "------------------------------------------------" << endl;

    SkipList l2;

    Player q1{201, "Virat", 880, 12};
    Player q2{202, "Dhoni", 910, 18};
    Player q3{203, "Ishaan", 910, 10};
    Player q4{204, "Axar", 840, 25};
    Player q5{205, "Jadeja", 970, 15};

    cout << "Inserting Players" << endl;
    l2.insertPlayer(q1);
    l2.insertPlayer(q2);
    l2.insertPlayer(q3);
    l2.insertPlayer(q4);
    l2.insertPlayer(q5);

    cout << "\nLeaderboard after insertion:\n";
    l2.displayLeaderboard();

    cout << "\nSkip List Structure:\n";
    l2.displaySkipListStructure();

    cout << "\nSearching Player with ID 203:\n";
    Node *found2 = l2.searchPlayer(203);

    if (found2 != nullptr)
        cout << "Player Found. Score = " << found2->pdata.pscore << " Name= " << found2->pdata.pname << endl;
    else
        cout << "Player not found\n";

    cout << "\nRank of Player 203: ";
    cout << l2.getRank(203) << endl;

    cout << "\nUpdating score of Player 201 to 990\n";
    l2.updateScore(201, 990);

    cout << "\nLeaderboard after score update:\n";
    l2.displayLeaderboard();

    cout << "\nSkip List Structure:\n";
    l2.displaySkipListStructure();

    cout << "\nDeleting Player 204\n";
    l2.deletePlayer(204);

    cout << "\nLeaderboard after deletion:\n";
    l2.displayLeaderboard();

    cout << "\nTop 3 Players:\n";
    l2.getTopK(3);

    cout << "\nFinal Skip List Structure:\n";
    l2.displaySkipListStructure();

    return 0;
}