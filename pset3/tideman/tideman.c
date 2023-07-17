#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i]) == 0)
        {
            ranks[rank] = i;
            return true;
        }
    }
    return 0;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            int rank_i = 0;
            int rank_j = 0;

            for (int n = 0; n < candidate_count; n++)
            {
                if (ranks[n] == i)
                {
                    rank_i = n;
                }
            }

            for (int m = 0; m < candidate_count; m++)
            {
                if (ranks[m] == j)
                {
                    rank_j = m;
                }
            }

            if (rank_i > rank_j)
            {
                preferences[i][j] += 0;
            }
            else if (rank_i < rank_j)
            {
                preferences[i][j]++;
            }
            else if (rank_i == rank_j)
            {
                preferences[i][j] = 0;
            }
        }
    }
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    int tmp_pi = 0;
    int tmp_pii = 0;
    int n = 0;

    for (int i = 0; i < (candidate_count - 1); i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            tmp_pi = preferences[i][j];
            tmp_pii = preferences[j][i];

            if (tmp_pi > tmp_pii)
            {
                pairs[n].winner = i;
                pairs[n].loser = j;
                n++;
                pair_count++;
            }
            else if (tmp_pi < tmp_pii)
            {
                pairs[n].winner = j;
                pairs[n].loser = i;
                n++;
                pair_count++;
            }
        }
    }
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    int delta_i = 0;
    int delta_j = 0;

    for (int i = 0; i < pair_count; i++)
    {
        for (int j = 0; j < pair_count; j++)
        {
            int x = pairs[i].winner;
            int y = pairs[i].loser;
            delta_i = preferences[x][y] - preferences[y][x];

            int n = pairs[j].winner;
            int m = pairs[j].loser;
            delta_j = preferences[n][m] - preferences[m][n];

            if (delta_i > delta_j)
            {
                pairs[i].winner = n;
                pairs[i].loser = m;

                pairs[j].winner = x;
                pairs[j].loser = y;
            }
        }
    }
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    for (int n = 0; n < pair_count; n++)
    {
        int index = 0;
        int num = 0;
        int loop_index = 0;

        int x = pairs[n].winner;
        int y = pairs[n].loser;

        locked[x][y] = true;
        num = x;

        while (index < candidate_count)
        {
            index++;

            for (int i = 0; i < candidate_count; i++)
            {
                if (locked[num][i] == true)
                {
                    num = i;
                }
            }

            if (num == x)
            {
                loop_index = 1;
                index = candidate_count;
            }
            else if (num != x && index == candidate_count - 1)
            {
                loop_index = 0;
            }
        }

        if (loop_index == 1)
        {
            locked[x][y] = false;
        }
        else if (loop_index == 0)
        {
            locked[x][y] = true;
        }
    }

}

// Print the winner of the election
void print_winner(void)
{
    int source[candidate_count];
    int index = 0;

    for (int i = 0; i < candidate_count; i++)
    {
        source[i] = 0;
    }

    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[i][j] == false)
            {
                source[j]++;
            }
            else
            {
                source[j] += 0;
            }
        }
    }

    for (int i = 0; i < candidate_count; i++)
    {
        if (source[i] == candidate_count)
        {
            index = i;
        }
    }
    printf("%s\n", candidates[index]);
}