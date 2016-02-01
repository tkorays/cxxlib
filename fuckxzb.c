#include <stdlib.h>
#include <stdio.h>
#include <string.h>


int get_data_tpl(const char* src,int src_size,const char* tpl,int tpl_size,struct usrdata* data);

int main(int argc,char* argv[]){
	const char* src = "<abc=\"wocao\"asdkljfkajdsfjc>nimeifu</abc><caoni>abc</caoni>";
	const char* tpl = "<abc=\"*(c>)?(</a)bc><caoni>?(</cao)ni>";
	char result[24];
	int ret = get_data_tpl(src, strlen(src), tpl, strlen(tpl), result, 12);

	printf("结果: %s,匹配结果:\"%s\",\"%s\"", ret?"OK":"NMB", result,result+12);
	getchar();
	return 0;
}

/* 
 * 声明：
 *     1. 输入的正确性由调用者保证，本函数不做任何保证
 *     2. 由于输入导致的后果，一切由调用者承担，和本函数无关
 *     3. 如果调用者明知该输入可能会导致失败仍一意孤行，调用者需要自断jj
 *     4. 如果函数内部出现错误，一定是调用者的问题
 */
int get_data_tpl(const char* src, int src_size, const char* tpl, int tpl_size, char* data,int item_size){
	int i, j, k, l, m, n, h;
	char sel[8+1]; // 结束字符不超过8个，这在模板定义中已经说明
	int temp_char_max_size = 8;
	int match = 0;
	int data_count = 0;


	i = 0;
	j = 0;
	while (i < src_size && j < tpl_size){
		// ignore
		if (tpl[j] == '*'){
			l = 0;
			for (k = 2; k < temp_char_max_size + 2; k++){
				if (tpl[j + k] != ')'){
					sel[l++] = tpl[j + k];
				}else{
					break;
				}
			}
			sel[l] = '\0';
			j =j + l + 3; // 更新tpl游标

			k = i;
			n = i;
			m = 0;
			// 修改src的游标
			while ((k < src_size) && m < l){
				if (src[k] != sel[m]){
					m = 0;
					k = ++n;;
				}else{
					k++;
					m++;
				}
				if (m == l){
					i = k; // 更新src游标
					break;
				}
			}
		}
		
		// k,l,m,n可以再次使用
		// match
		if (tpl[j] == '?'){ // 原谅我这一生不羁放纵爱粘贴
			l = 0;
			for (k = 2; k < temp_char_max_size + 2; k++){
				if (tpl[j + k] != ')'){
					sel[l++] = tpl[j + k];
				}
				else{
					break;
				}
			}
			sel[l] = '\0';
			j = j + l + 3; // 更新tpl游标

			k = i; // k(i)记录最后地址，k自动更新，i最后更新
			n = i; // n记录起始地址，自动更新
			m = 0; 
			h = i; // 保存i
			// 修改src的游标
			while ((k < src_size) && m < l){
				if (src[k] != sel[m]){
					m = 0;
					k = ++n;
				}else{
					k++;
					m++;
				}
				if (m == l){
					i = k; // 更新src游标
					break;
				}
			}
			// 存储
			for (m = 0; m < (i - h-l); m++){
				data[data_count*item_size + m] = src[h + m];
			}
			data[data_count*item_size + m] = '\0'; // 最后补上\0
			data_count++;
		}
		j++;
		i++;
	}

	return 1;
}