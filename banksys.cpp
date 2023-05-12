#include"total.h"
int main() {
	int n = 0;
	while (1) {
		printf_menu();
		scanf_s("%d", &n);
		if (n == 1) {
			create_account();
		}
		else if (n == 2) {
			login();
		}
		else if (n == 3) {
			admin();
		}
		else if (n == 4) {
			exit(0);
		}
	}






































}
