#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> PII;

int offset[5] = {0, 1, 0, -1, 0};
int width;
int height;
vector<string> input{};

struct Wind {
    int x;
    int y;
    int dir;
    
    Wind(int y, int x, int dir)
    {
        this->x = x;
        this->y = y;
        this->dir = dir;
    }
    
    void move()
    {
        this->x += offset[dir];
        this->y += offset[dir + 1];
        if (this->x == 0)
        {
            this->x = width - 2;
        }
        else if (this->x == width - 1)
        {
            this->x = 1;
        }
        else if (this->y == 0)
        {
            this->y = height - 2;
        }
        else if (this->y == height - 1)
        {
            this->y = 1;
        }
    }
};

set<Wind*> currWindPos{};

int minTimeToGo(int startX, int startY, int endX, int endY)
{
    queue<PII> q{};
    set<PII> validSpots{};
    int currMin = 0;
    validSpots.insert({startY, startX});
    q.emplace(startY, startX);
    while (!validSpots.count({endY, endX}))
    {
        for (auto & wind : currWindPos)
        {
            input[wind->y][wind->x] = '.';
        }
        for (auto & wind : currWindPos)
        {
            wind->move();
            input[wind->y][wind->x] = 'B';
        }
        int n = q.size();
        set<PII> newValid{};
        for (int i = 0; i < n; ++i)
        {
            PII curr = q.front();
            q.pop();
            if (input[curr.first][curr.second] == '.' && !newValid.count(curr))
            {
                q.emplace(curr);
                newValid.insert(curr);
            }
            for (int k = 0; k < 4; ++k)
            {
                int nx = curr.second + offset[k];
                int ny = curr.first + offset[k + 1];
                if (nx > 0 && nx < width - 1 && ny >= 0 && ny < height && 
                input[ny][nx] == '.' && !newValid.count({ny, nx}))
                {
                    q.emplace(ny, nx);
                    newValid.insert({ny, nx});
                }
            }
        }
        ++currMin;
        validSpots = newValid;
    }
    return currMin;
}

int main()
{
    string s;
    while (getline(cin, s))
    {
        input.emplace_back(s);
    }
    width = input[0].length();
    height = input.size();
    for (int i = 1; i < height - 1; ++i)
    {
        for (int j = 1; j < width - 1; ++j)
        {
            if (input[i][j] == '^')
            {
                currWindPos.insert(new Wind(i, j, 2));
            }
            else if (input[i][j] == 'v')
            {
                currWindPos.insert(new Wind(i, j, 0));
            }
            else if (input[i][j] == '<')
            {
                currWindPos.insert(new Wind(i, j, 3));
            }
            else if (input[i][j] == '>')
            {
                currWindPos.insert(new Wind(i, j, 1));
            }
        }
    }
    int timeTaken = 0;
    timeTaken += minTimeToGo(1, 0, width - 2, height - 1);
    printf("Part 1: %d\n", timeTaken);
    timeTaken += minTimeToGo(width - 2, height - 1, 1, 0);
    timeTaken += minTimeToGo(1, 0, width - 2, height - 1);
    printf("Part 2: %d\n", timeTaken);
    return 0;
}
