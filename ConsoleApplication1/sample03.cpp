#include <iostream>
#include <iomanip>
#include <vector>
int main()
{
	int ���͒l;
	if (std::cin >> ���͒l) {
		if (���͒l == -1) {
			std::cout << "�n�߂̓��͒l�� -1 �ł��������߁A�����ł��܂���ł����B\n";
			return EXIT_FAILURE;
		}
		else {
			//�f�[�^���P���������͂��ꂽ
			std::vector<int> �z��{���͒l};
			int ���v = ���͒l;//�����l
			//�J��Ԃ��Ȃ� for ��
			for (;;) {
				if (std::cin >> ���͒l) {
					//���͐���
					if (���͒l == -1)
						break;//for ���I���
					else {
						�z��.push_back(���͒l);
						���v += ���͒l;
					}
				}
				else {
					//���s
					break;
				}
			}
			//for�����I������Ƃ���œ��͂��ꂽ�L���ȃf�[�^�̌����u�f�[�^�����v�ɔ��f����Ă���
			const double ���ϓ_ = (double)���v / �z��.size();
			//range-based for ��
			for (const auto& �e�v�f : �z��) {
				//�������Z�q(conditional operator)�Ńf�[�^�I��
				std::cout << "No." << std::setw(2) << 1 + (&�e�v�f - &�z��.front()) << '\t' << �e�v�f << '\t' << (�e�v�f < ���ϓ_ ? "���ϓ_����" : "���ϓ_�ȏ�") << '\n';
			}
			return EXIT_SUCCESS;
		}
	}
	else {
		//�f�[�^���͎��s
		std::cout << "�n�߂̓��͂����s���܂����B\n";
		return EXIT_FAILURE;
	}
}
