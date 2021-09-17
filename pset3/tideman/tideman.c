/* Tideman offical is the offical submission,
This was made to test merge sort on custom struct */


#include <cs50.h>
#include <stdio.h>
#include <string.h>

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
bool cycle(int start, int end);
void merge (pair arr[], int l, int m, int r);
void sort_pairs(pair arr[], int l, int r);
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
    // Pair count - 1 since we ++ pair count every iteration
    // sort_pairs(pairs, 0, pair_count - 1);
    sort_pairs(pairs, 0, pair_count - 1);
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    // For loop that checks if the name is in candidate names
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i]) == 0)
        {
            ranks[rank] = i;
            return true;
        }
    }
    // If name is not in candidates
    return false;
}


// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    /*Updating the preferences using 2 for loops efficently
    by starting from the end of ranks */
    for (int i = candidate_count - 2; i >= 0; i--)
    {
        for(int j = i + 1; j < candidate_count; j ++)
        {
            int winner = ranks[i];
            int loser = ranks [j];
            preferences[winner][loser]++;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
            else if (preferences[i][j] < preferences[j][i])
            {
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = i;
                pair_count++;
            }
        }
    }
    return;
}


// Takes in a proposed pair and test to see if it will return a cycle
bool cycle(int start, int end)
{
    /* Base case
    If the locked pair circles back to the winner returns true */
    if (end == start)
    {
        return true;
    }

    for(int i = 0; i < candidate_count; i++)
    {
        if (locked[end][i])
        {
            if (cycle(start, i))
            {
                return true;
            }
        }
    }
    return false;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // Looping through all the pairs
    for (int i = 0; i < pair_count; i++)
    {
        // If no cycle is created, lock the pair
        if (!cycle(pairs[i].winner, pairs[i].loser))
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }
    return;
}

// Print the winner of the election
void print_winner(void)
{
    /* definition of "source of graph" from wikipedia:
    A source, in a directed graph, is a vertex with no incoming edges (in-degree equals 0).
    Translation: the winner is the person who does not have any incoming edges, or in this example,
    does not have any losses
    */

    /* Iterate over each row (candidate)
    if they have any loses locked[j (opponenents)][ i (candidate) ]
    then that candidate lost */
    for (int i = 0; i < candidate_count; i++)
    {
        bool loser = false;
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[j][i])
            {
                loser = true;
                break;
            }
        }

        if (loser) continue;
        else
        {
            printf("%s\n", candidates[i]);
        }
    }
    return;
}


/*
TRIED TO PERFORM MERGE SORT BUT FAILED AND GAVE UP :/
*/
void merge (pair arr[], int l, int m, int r)
{
    // Variables to loop over
    int i, j, k;
    // Number of elements to go into the temp arrays
    // n1 = m - l + 1 since the LHS of merge sort
    // includes m and indexing starts at 0. N1 is the # of elements
    // and therefore has to include the + 1 in order to work //
    int n1 = m - l + 1;
    int n2 = r - m;

    // Temp arrays used for comparison
    pair L[n1], R[n2];

     // Copy data to temp arrays L[] and R[] //
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1+ j];


    // Setting the variable values
    i = 0; // Initial index of the L subarray
    j = 0; // Intial index of the R subarray
    k = l; // Intial index of the merged subarray - starts at index of LHS

    while (i < n1 && j < n2)
    {
        // Comparing the preferences array of pair index i
        if (preferences[L[i].winner][L[i].loser] >= preferences[L[j].winner][L[j].loser])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // Copy the remaining elements of L[], if there
    //   are any //
    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }

    // Copy the remaining elements of R[], if there
    //   are any //
    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }

    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(pair arr[], int l, int r)
{
    if (l < r)
    {
        int m = (l + (r - 1)) / 2;

        sort_pairs(arr, l, m);
        sort_pairs(arr, m + 1, r);

        merge(arr, l , m , r);
    }
    return;
}


