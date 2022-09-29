#include <iostream>
#include <iomanip>
#define	このプログラムにおいての最大データ件数  3  //なるべく長い名前にしておく

int main()
{
	int 入力値;
	if (std::cin >> 入力値) {
		if (入力値 == -1) {
			std::cout << "始めの入力値が -1 であったため、処理できませんでした。\n";
			return EXIT_FAILURE;
		}
		else {
			//データが１個正しく入力された
			int 配列[このプログラムにおいての最大データ件数];
			int 合計 = (配列[0] = 入力値);//初期値
			int データ件数 = 1;
			//繰り返すなら for 文
			for (;;) {
				if (データ件数 == このプログラムにおいての最大データ件数)
					break;
				else if (std::cin >> 入力値) {
					//入力成功
					if (入力値 == -1)
						break;//for 文終わり
					else
						合計 += 配列[データ件数++] = 入力値;
				}
				else {
					//失敗
					break;
				}
			}
			//for文が終わったところで入力された有効なデータの個数が「データ件数」に反映されている
			const double 平均点 = (double)合計 / データ件数;
			for (int i = 0; i < データ件数; ++i) {
				//条件演算子(conditional operator)でデータ選択
				std::cout << "No." << std::setw(2) << 1 + i << '\t' << 配列[i] << '\t' << (配列[i] < 平均点 ? "平均点未満" : "平均点以上") << '\n';
			}
			return EXIT_SUCCESS;
		}
	}
	else {
		//データ入力失敗
		std::cout << "始めの入力が失敗しました。\n";
		return EXIT_FAILURE;
	}
}
