#include <iostream>
#include <iomanip>
#include <vector>
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
			std::vector<int> 配列{入力値};
			int 合計 = 入力値;//初期値
			//繰り返すなら for 文
			for (;;) {
				if (std::cin >> 入力値) {
					//入力成功
					if (入力値 == -1)
						break;//for 文終わり
					else {
						配列.push_back(入力値);
						合計 += 入力値;
					}
				}
				else {
					//失敗
					break;
				}
			}
			//for文が終わったところで入力された有効なデータの個数が「データ件数」に反映されている
			const double 平均点 = (double)合計 / 配列.size();
			//range-based for 文
			for (const auto& 各要素 : 配列) {
				//条件演算子(conditional operator)でデータ選択
				std::cout << "No." << std::setw(2) << 1 + (&各要素 - &配列.front()) << '\t' << 各要素 << '\t' << (各要素 < 平均点 ? "平均点未満" : "平均点以上") << '\n';
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
