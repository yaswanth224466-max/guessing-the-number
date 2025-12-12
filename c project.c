#include <stdio.h>

void splitDigits(int n, int d[3]) {
    // assumes n is a 3-digit non-negative number
    d[2] = n % 10; n /= 10;
    d[1] = n % 10; n /= 10;
    d[0] = n % 10;
}

// returns wrong-position count; also fills correctPos by reference
int countMatches(int secret, int guess, int *correctPos) {
    int s[3], g[3];
    splitDigits(secret, s);
    splitDigits(guess, g);

    // mark matched positions
    int usedSecret[3] = {0,0,0}; // 1 if that secret digit already matched (correct-pos or used)
    int usedGuess[3]  = {0,0,0};

    *correctPos = 0;
    // 1) correct-position matches
    for (int i = 0; i < 3; i++) {
        if (s[i] == g[i]) {
            (*correctPos)++;
            usedSecret[i] = 1;
            usedGuess[i] = 1;
        }
    }

    // 2) build frequency of remaining secret digits (0..9)
    int freq[10] = {0};
    for (int i = 0; i < 3; i++) {
        if (!usedSecret[i]) {
            int digit = s[i];
            freq[digit]++;
        }
    }

    // 3) count wrong-position matches by checking unmatched guess digits against freq
    int wrongPos = 0;
    for (int i = 0; i < 3; i++) {
        if (!usedGuess[i]) {
            int digit = g[i];
            if (freq[digit] > 0) {
                wrongPos++;
                freq[digit]--; // consume that secret digit
            }
        }
    }

    return wrongPos;
}

int main(void) {
    int secret1, secret2;
    int guess;

    printf("Player 1, enter your secret 3-digit number: ");
    scanf("%d", &secret1);

    printf("Player 2, enter your secret 3-digit number: ");
    scanf("%d", &secret2);

    int p1Done = 0, p2Done = 0;
    while (!(p1Done && p2Done)) {
        // Player 2 guesses Player 1's number
        if (!p1Done) {
            printf("\nPlayer 2, guess Player 1's number: ");
            scanf("%d", &guess);

            if (guess == secret1) {
                printf("Correct guess by Player 2!\n");
                p1Done = 1;
            } else {
                int correctPos = 0;
                int wrongPos = countMatches(secret1, guess, &correctPos);
                printf("%d correct-position, %d wrong-position matches.\n", correctPos, wrongPos);
            }
        }

        // Player 1 guesses Player 2's number
        if (!p2Done) {
            printf("\nPlayer 1, guess Player 2's number: ");
            scanf("%d", &guess);

            if (guess == secret2) {
                printf("Correct guess by Player 1!\n");
                p2Done = 1;
            } else {
                int correctPos = 0;
                int wrongPos = countMatches(secret2, guess, &correctPos);
                printf("%d correct-position, %d wrong-position matches.\n", correctPos, wrongPos);
            }
        }
    }

    printf("\nBoth players guessed correctly! Game over.\n");
    return 0;
}
