#include <iostream>
#include <iomanip>
#define	���̃v���O�����ɂ����Ă̍ő�f�[�^����  3  //�Ȃ�ׂ��������O�ɂ��Ă���

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
			int �z��[���̃v���O�����ɂ����Ă̍ő�f�[�^����];
			int ���v = (�z��[0] = ���͒l);//�����l
			int �f�[�^���� = 1;
			//�J��Ԃ��Ȃ� for ��
			for (;;) {
				if (�f�[�^���� == ���̃v���O�����ɂ����Ă̍ő�f�[�^����)
					break;
				else if (std::cin >> ���͒l) {
					//���͐���
					if (���͒l == -1)
						break;//for ���I���
					else
						���v += �z��[�f�[�^����++] = ���͒l;
				}
				else {
					//���s
					break;
				}
			}
			//for�����I������Ƃ���œ��͂��ꂽ�L���ȃf�[�^�̌����u�f�[�^�����v�ɔ��f����Ă���
			const double ���ϓ_ = (double)���v / �f�[�^����;
			for (int i = 0; i < �f�[�^����; ++i) {
				//�������Z�q(conditional operator)�Ńf�[�^�I��
				std::cout << "No." << std::setw(2) << 1 + i << '\t' << �z��[i] << '\t' << (�z��[i] < ���ϓ_ ? "���ϓ_����" : "���ϓ_�ȏ�") << '\n';
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
