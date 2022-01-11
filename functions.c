#include <stdio.h>
#include <string.h>

#define TRUE 1
#define FALSE 0
#define BOOL int

void reverse(char*);
void add2Int(char*, char*);
void mul2Int(char*, char*);
void absInt(char*);

int main(int argc, char const *argv[]) {
    char str1[512] = "5000000000000000000000000000000000000000000000000000000";
    char str2[512] = "5000000000000000000000000000000000000000000000000000000";
    mul2Int(str1, str2);
    printf("%s\n", str1);
    return 0;
}

void mul2Int(char* multiplied, char* multiply){

    int length1 = strlen(multiplied);
    int length2 = strlen(multiply);
    int result[length1 + length2];

    // zero production
    if (multiplied[0] == '0' || multiply[0] == '0'){
        multiplied[0] = '0';
        multiplied[1] = '\0';
        return;
    }

    // 初始化最大可能大小為 0
    for (int i = 0; i < length1 + length2; i++){
        result[i] = 0;
    }

    for (int i = length1 - 1; i >= 0; i--){
        for (int j = length2 - 1; j >= 0; j--){
            int mul = (multiplied[i] - '0') * (multiply[j] - '0');
            int pos1 = i + j;
            int pos2 = i + j + 1;
            // 疊加到 result 上
            int sum = mul + result[pos2];
            result[pos2] = sum % 10;
            result[pos1] += sum / 10;
        }
    }

    BOOL startWithZero = (result[0] == 0) ? TRUE : FALSE;
    int copyIdx = 0;
    // copy result to char array multiplied
    for (int i = 0; i < length1 + length2; i++){
        if (!startWithZero){
            multiplied[copyIdx++] = result[i] + '0';
        }else{
            if (result[i + 1] != 0){
                startWithZero = FALSE;
            }
        }
    }
    multiplied[copyIdx] = '\0'; // 字串結束
}

void add2Int(char* added, char* add){
    // 翻轉成可以循序加的形式
    reverse(added);
    reverse(add);
    // 紀錄並比較兩者誰長
    int length1 = strlen(added);
    int length2 = strlen(add);
    BOOL addedIsLonger = (length1 >= length2) ? TRUE : FALSE;
    int carry = 0;

    // 補零到等長
    if (addedIsLonger == TRUE){
        for (int i = length2; i < length1; i++){
            add[i] = '0';
        }
        add[length1] = '\0'; // 字串結尾
    }else{
        for (int i = length1; i < length2; i++){
            added[i] = '0';
        }
        added[length2] = '\0'; // 字串結尾
    }
    length1 = strlen(added); // 更新長度 (目前等長)
    for (int i = 0; i < length1; i++){
        int result = (added[i] - '0') + (add[i] - '0') + carry;
        if (result < 10){
            // 不用進位
            added[i] = result + '0';
            carry = 0;
        }else{
            // 需要進位
            added[i] = result - 10 + '0';
            carry = 1;
        }
    }
    // 判斷是否此時carry為零
    // 表示兩等長字串相加會溢位
    if (carry){
        added[length1] = '1';
        added[length1 + 1] = '\0';
    }
    reverse(added); // 最後翻轉到正確格式
}

void reverse(char* str){
    int i, j;
    char c;
    // 假設字串長度為 n
    // 將 0 和 n-1 調換,再換 1和 n-2,直到字串中間為止
    for (i = 0, j = strlen(str) - 1; i < j; i++, j--) {
        c = str[i];
        str[i] = str[j];
        str[j] = c;
    }
}

void absInt(char* Integer){
    if (Integer[0] == '-'){
        // 將負號之後往前移一位
        for (char* s = Integer; *s != 0; s++){
            *s = *(s + 1);
        }
    }
}
