#include <iostream>
#include <string.h>
#include <algorithm>

#define PLAYERA '1'
#define PLAYERB '2'
#define EMPTY '0'
#define MAX 100
#define MIN -100

using namespace std;

class board
{
	int N;
	int M;
	int K;
public:
	char** arr;

	board(int n, int m, int k) : N(n), M(m), K(k)
	{
		arr = new char* [n];
		for (int i = 0; i < n; ++i)
			arr[i] = new char[m];
	}

	void GenAllPosMov(char Player)
	{
		if (CheckWin(Player))
		{
			cout << EMPTY << endl;
		}
		else
		{
			CountMoves();
			AllMoves(Player);
		}
	}

	void GenAllPosMovCutIfGameOverCut(char Player)
	{
		if (CheckWin(Player))
		{
			cout << EMPTY << endl;
		}
		else if (CheckIfCanWin(Player))
		{
			cout << '1' << endl;
			PrintBoard();
		}
		else
		{
			CountMoves();
			AllMoves(Player);
		}
	}

	void SolveGameState(char Player)
	{
		int score = MiniMax(Player, 0, true, MIN, MAX);

		if (score == 10 && Player == PLAYERA)
			cout << "FIRST_PLAYER_WINS" << endl;
		else if (score == 10 && Player == PLAYERB)
			cout << "SECOND_PLAYER_WINS" << endl;
		else if (score == -10 && Player == PLAYERA)
			cout << "SECOND_PLAYER_WINS" << endl;
		else if (score == -10 && Player == PLAYERB)
			cout << "FIRST_PLAYER_WINS" << endl;
		else
			cout << "BOTH_PLAYERS_TIE" << endl;
	}

	bool isMovesLeft() const
	{
		for (int i = 0; i < N; i++)
			for (int j = 0; j < M; j++)
				if (arr[i][j] == EMPTY)
					return true;

		return false;
	}

	int MiniMax(char Player,int depth, bool isMax, int alpha, int beta)
	{
		char P1,P2;
		int score;

		if (Player == PLAYERA)
		{
			P1 = PLAYERB;
			P2 = PLAYERA;
		}
		else
		{
			P1 = PLAYERA;
			P2 = PLAYERB;
		}

		if (CheckWin(P1)) 
			score = 10;
		else if (CheckWin(P2)) 
			score = -10;
		else 
			score = 0;
		
		if (score == 10) 
			return score;
		else if (score == -10) 
			return score;

		if (isMovesLeft() == false) 
			return 0;

		if (isMax)
		{
			int best = MIN;
			for (int i = 0; i < N; i++)
				for (int j = 0; j < M; j++)
					if (arr[i][j] == EMPTY)
					{
						arr[i][j] = P2;
						best = max(best,MiniMax(P2, depth + 1, !isMax, alpha, beta));
						arr[i][j] = EMPTY;
						alpha = max(alpha, best);
						if (beta <= alpha)
							break;
					}
			return best;
		}
		else
		{
			int best = MAX;
			for (int i = 0; i < N; i++)
				for (int j = 0; j < M; j++)
					if (arr[i][j] == EMPTY)
					{
						arr[i][j] = P1;
						best = min(best, MiniMax(P2, depth + 1, !isMax, alpha, beta));
						arr[i][j] = EMPTY;
						beta = min(beta, best);
						if (beta <= alpha)
							break;
					}
			return best;
		}
	}

	bool CheckRow(char Player,int x,int y) const
	{
		for (int k = 0; k < K; k++)
		{
			if (y + k >= M)					
				return false;
			else if (arr[x][y + k] == Player)	
				continue;
			else 
				return false;
		}
		return true;
	}

	bool CheckCollum(char Player, int x, int y) const
	{
		for (int k = 0; k < K; k++)
		{
			if (x + k >= N)		
				return false;
			else if (arr[x + k][y] == Player)
				continue;
			else
				return false;
		}
		return true;
	}

	bool CheckDaiagonal1(char Player, int x, int y) const
	{
		for (int k = 0; k < K; k++)
		{
			if (x + k >= N || y + k >= M)
				return false;
			else if (arr[x + k][y + k] == Player)
				continue;
			else
				return false;
		}
		return true;
	}

	bool CheckDaiagonal2(char Player, int x, int y) const
	{
		for (int k = 0; k < K; k++)
		{
			if (x + k >= N || y - k < 0)
				return false;
			else if (arr[x + k][y - k] == Player)
				continue;
			else
				return false;
		}
		return true;
	}

	bool CheckWin(char Player) const
	{
		char P;
		if (Player == PLAYERA) P = PLAYERB;
		else P = PLAYERA;

		for (int i = 0; i < N; i++)
			for (int j = 0; j < M; j++)
				if (arr[i][j] == P)
					if (CheckRow(P, i, j) || CheckCollum(P, i, j) || CheckDaiagonal1(P, i, j) || CheckDaiagonal2(P, i, j))
						return true;

		return false;
	}

	bool CheckIfCanWin(char Player) const
	{
		char P;
		if (Player == PLAYERA) P = PLAYERB;
		else P = PLAYERA;

		for (int i = 0; i < N; i++)
			for (int j = 0; j < M; j++)
				if (arr[i][j] == EMPTY)
				{
					arr[i][j] = Player;
					if (CheckWin(P))
						return true;
					else
						arr[i][j] = EMPTY;
				}

		return false;
	}

	void FillBoard()
	{
		for (int i = 0; i < N; i++)
			for (int j = 0; j < M; j++)
				cin >> arr[i][j];
	}

	void CountMoves() const
	{
		int count = 0;
		for (int i = 0; i < N; i++)
			for (int j = 0; j < M; j++)
				if (arr[i][j] == EMPTY)
					count++;

		cout << count << endl;
	}

	void AllMoves(char Player)
	{
		for (int i = 0; i < N; i++)
			for (int j = 0; j < M; j++)
				if (arr[i][j] == EMPTY)
				{
					arr[i][j] = Player;
					PrintBoard();
					arr[i][j] = EMPTY;
				}
	}

	void PrintBoard() const
	{
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < M; j++)
				cout << arr[i][j] << " ";
			cout << endl;
		}
	}

	~board()
	{
		for (int i = 0; i < N; ++i)
			delete[] arr[i];
		delete[] arr;
	}
};

int main()
{
	char command1[] = "GEN_ALL_POS_MOV";
	char command2[] = "GEN_ALL_POS_MOV_CUT_IF_GAME_OVER";
	char command3[] = "SOLVE_GAME_STATE";
	char command[33];
	int N = 0, M = 0, K = 0;
	char Player;

	while (!cin.eof())
	{
		cin >> command >> N >> M >> K >> Player;
		board b(N, M, K);
		b.FillBoard();
		if (strcmp(command,command1) == 0)
		{
			b.GenAllPosMov(Player);
		}
		else if (strcmp(command, command2) == 0)
		{
			b.GenAllPosMovCutIfGameOverCut(Player);
		}
		else if (strcmp(command, command3) == 0)
		{
			b.SolveGameState(Player);
		}
	}
}
