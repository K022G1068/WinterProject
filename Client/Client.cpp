#include"Player.h"
#include"Map.h"
#include <Novice.h>

const char kWindowTitle[] = "K022G1068";
const int kWindowWidth = 1280;
const int kWindowHeight = 720;

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, kWindowWidth, kWindowHeight);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

	int gameScene = 0;

	Player* player = new Player();
	Map* map = new Map();

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///
		
		///
		/// ↑更新処理ここまで
		///
		/// 
	/*	switch (gameScene)
		{
			case GameStatus::Game_Title:
			{
				if (keys[DIK_RETURN] && preKeys[DIK_RETURN] == 0)
				{
					gameScene = GameStatus::Game_MakeRoom;
				}
				if (keys[DIK_SPACE] && preKeys[DIK_SPACE] == 0)
				{
					gameScene = GameStatus::Game_Start;
				}

				gameTitle->Draw();
				break;
			}
	
			case GameStatus::Game_Search:
			{

				break;
			}

			case GameStatus::Game_MakeRoom:
			{

				break;
			}

			case GameStatus::Game_Start:
			{
				gameStart->Update(keys, preKeys);

				gameStart->Draw();
				break;
			}

			case GameStatus::Game_Over:
			{

				break;
			}*/
		
		player->Update(keys, preKeys);
		///
		/// ↓描画処理ここから
		///
		map->DrawMap();
		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
