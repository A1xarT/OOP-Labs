#include "scanner.h"
void create_db(const char* csv, const char* db) {
	FILE *f, *g;
	char c; int str_recs = 1, i, j, k = 0;
	SCAN_INFO temp, *mas;
	fopen_s(&f, csv, "r");
	fopen_s(&g, db, "w");
	if (f == NULL) {
		fclose(g);
		return;
	}
	while (!feof(f)) { 
		fread(&c, 1, 1, f); 
		if (c == '\n') str_recs++; 
	}
	fwrite(&str_recs, sizeof(int), 1, g);
	fseek(f, 0, 0);
	mas = (SCAN_INFO*)malloc(sizeof(SCAN_INFO) * str_recs);
	str_recs = 0;
	while (!feof(f)) {
		fread(&c, 1, 1, f);						// manufacturer
		i = 0;
		while ((c != ';')&&(c != '\n')) {		
			temp.manufacturer[i++] = c;
			fread(&c, 1, 1, f);
		}
		temp.manufacturer[i] = '\0';			
		fread(&c, 1, 1, f);
		i = 0;
		while ((c != ';') && (c != '\n')) {		// model
			temp.model[i++] = c;
			fread(&c, 1, 1, f);
		}
		temp.model[i] = '\0';
		fscanf_s(f, "%d", &temp.year);			// year
		fseek(f, 1, 1);
		fscanf_s(f, "%lf", &temp.price);			// price
		fseek(f, 1, 1);
		fscanf_s(f, "%d", &temp.x_size);		// x_size
		fseek(f, 1, 1);
		fscanf_s(f, "%d", &temp.y_size);		// y_size
		int flag = 1;
		for (j = 0; j < k; j++) {				// checking for dublicate
			if ((mas[j].price == temp.price) && (mas[j].year == temp.year) && (mas[j].x_size == temp.x_size) && (mas[j].y_size == temp.y_size)
				&& (!strcmp(mas[j].manufacturer, temp.manufacturer)) && (!strcmp(mas[j].model, temp.model))) {
				flag = 0;
				break;
			}
		}
		if (flag == 1) {
			temp.id = ++k;						// id
			fwrite(&temp, sizeof(SCAN_INFO), 1, g);
			mas[k - 1] = temp;
			str_recs++;
		}
		if (!feof(f)) fread(&c, 1, 1, f);
	}
	free(mas);
	fseek(g, 0, 0);
	fwrite(&str_recs, sizeof(int), 1, g);
	_fcloseall();
}

int make_index(const char* db, const char* field_name) {
	FILE* f, * g;
	int i, j, k, str_recs, index_tmp, swap, len = strlen(field_name), *indexes;
	double tmp, *numbersort;
	char** strsort, * tmp_ch, * file_name = (char*)malloc(len + 5);
	SCAN_INFO* mas;
	strcpy_s(file_name, len + 5, field_name);
	strcat_s(file_name, len + 5, ".idx");
	fopen_s(&f, db, "r");
	fopen_s(&g, file_name, "w");
	if (f == NULL) {
		fclose(g);
		return 0;
	}
	fread(&str_recs, sizeof(int), 1, f);
	strsort = (char**)malloc(sizeof(char*)*str_recs);
	for (j = 0; j < str_recs; j++) 
		strsort[j] = (char*)malloc(127);
	mas = (SCAN_INFO*)malloc(sizeof(SCAN_INFO) * str_recs); // array of structures that 
	for (j = 0; j < str_recs; j++)										// contains full information of db-file
		fread(&mas[j], sizeof(SCAN_INFO), 1, f);
	numbersort = (double*)malloc(sizeof(double) * str_recs);
	indexes = (int*)malloc(sizeof(int) * str_recs);
	for (j = 0; j < str_recs; j++) indexes[j] = mas[j].id;
	numbersort[0] = -1;					// setting flag to know what to sort: strings or numbers
	if (!strcmp(field_name, "id")) {
		for (j = 0; j < str_recs; j++)
			numbersort[j] = mas[j].id;
	}
	if (!strcmp(field_name, "year")) {
		for (j = 0; j < str_recs; j++)
			numbersort[j] = mas[j].year;
	}
		
	if (!strcmp(field_name, "price")) {
		for (j = 0; j < str_recs; j++)
			numbersort[j] = mas[j].price;
	}
			
	if (!strcmp(field_name, "x_size")) {
		for (j = 0; j < str_recs; j++)
			numbersort[j] = mas[j].x_size;
	}
				
	if (!strcmp(field_name, "y_size")) {
		for (j = 0; j < str_recs; j++)
			numbersort[j] = mas[j].y_size;
	}
					
	if (!strcmp(field_name, "manufacturer")) {
		for (j = 0; j < str_recs; j++)
			strcpy_s(strsort[j], strlen(mas[j].manufacturer) + 1, mas[j].manufacturer);
	}
	if (!strcmp(field_name, "model")) {
		for (j = 0; j < str_recs; j++)
			strcpy_s(strsort[j], strlen(mas[j].model) + 1, mas[j].model);
	}
	if (numbersort[0] != -1) {					// for sorting numbers 
		for (i = str_recs - 1; i >= 0; i--) {
			swap = 1;
			for (k = 0; k < i; k++) {
				if (numbersort[k] >= numbersort[k + 1]) {
					tmp = numbersort[k];
					numbersort[k] = numbersort[k + 1];
					numbersort[k + 1] = tmp;
					tmp = indexes[k];
					indexes[k] = indexes[k + 1];
					indexes[k + 1] = tmp;
					swap = 0;
				}
			}
			if (swap == 1) break;
		}
	}											
	else {										// for sorting strings
		tmp_ch = (char*)malloc(127);
		for (i = str_recs - 1; i >= 0; i--) {
			swap = 1;
			for (k = 0; k < i; k++) {
				if (strcmp(strsort[k], strsort[k + 1]) > 0) {
					strcpy_s(tmp_ch, strlen(strsort[k])+1, strsort[k]);
					strcpy_s(strsort[k], strlen(strsort[k+1])+1, strsort[k+1]);
					strcpy_s(strsort[k+1], strlen(tmp_ch)+1, tmp_ch);
					index_tmp = indexes[k];
					indexes[k] = indexes[k + 1];
					indexes[k + 1] = index_tmp;
					swap = 0;
				}
			}
			if (swap == 1) break;
		}
		free(tmp_ch);
	}
	for (j = 0; j < str_recs; j++)
		fprintf(g, "%d ", indexes[j]);
	_fcloseall();
	free(indexes); free(numbersort); free(file_name); free(mas);
	for (j = 0; j < str_recs; j++) free(strsort[j]);
	return 1;
}
RECORD_SET* get_recs_by_index(const char* dba, char* indx_field) {
	FILE* f, * g;
	int i = 0, j, k, l = 0, flag, indexes_q = 0, records_q;
	int* indexes;
	char* file_name = (char*)malloc(strlen(indx_field)+5);
	strcpy_s(file_name, strlen(indx_field)+ 5, indx_field);
	strcat_s(file_name, strlen(indx_field)+ 5, ".idx");
	RECORD_SET* bundle;
	SCAN_INFO* recs_mas, *check_mas;
	fopen_s(&f, dba, "r");
	fopen_s(&g, file_name, "r");
	if ((f == NULL) || (g == NULL)) return NULL;
	bundle = (RECORD_SET*)malloc(sizeof(RECORD_SET));
	while (fscanf_s(g, "%d", &j) != EOF) indexes_q++;
	recs_mas = (SCAN_INFO*)malloc(sizeof(SCAN_INFO) * indexes_q);
	indexes = (int*)malloc(sizeof(int) * indexes_q);
	rewind(g);
	while (fscanf_s(g, "%d", &indexes[i])!= EOF) {
		i++;
	}
	fread(&records_q, sizeof(int), 1, f);
	check_mas = (SCAN_INFO*)malloc(sizeof(SCAN_INFO) * records_q);
	for (i = 0; i < records_q; i++) fread(&check_mas[i], sizeof(SCAN_INFO), 1, f);
	fseek(f, sizeof(int), SEEK_SET);
	for (j = 0; j < indexes_q; j++) {
		flag = 0;
		for (i = 0; i < records_q; i++) {
			if (check_mas[i].id == indexes[j]) {
				flag = 1;
				break;
			}
		}
		if (1 == flag) {
			for (k = 0; k < i + 1; k++) {
				fread(&recs_mas[l], sizeof(SCAN_INFO), 1, f);
			}
			fseek(f, sizeof(int), SEEK_SET);
			l++;
		}
	}
	
	bundle->rec_nmb = indexes_q;
	bundle->recs = recs_mas;
	_fcloseall();
	free(indexes);
	return bundle;
}
void reindex(const char* db) {
	make_index(db, "id");
	make_index(db, "manufacturer");
	make_index(db, "model");
	make_index(db, "year");
	make_index(db, "price");
	make_index(db, "x_size");
	make_index(db, "y_size");
}
void del_scanner(const char* db, int id) {
	int i, numb, idFlag = 0;
	SCAN_INFO* mas;
	FILE* f;
	fopen_s(&f, db, "r");
	if (f == NULL) return;
	fread(&numb, sizeof(int), 1, f);
	mas = (SCAN_INFO*)malloc(sizeof(SCAN_INFO) * numb);
	for (i = 0; i < numb; i++) {
		if(!fread(&mas[i], sizeof(SCAN_INFO), 1, f)) break;
		if (mas[i].id == id) {
			i--;
			idFlag = 1;
		}
	}
	if (!idFlag) {					// if program did not find the id
		free(mas);
		fclose(f);
		return;
	}
	numb -= 1;
	fclose(f);
	fopen_s(&f, db, "w");
	fwrite(&numb, sizeof(int), 1, f);
	for (i = 0; i < numb; i++)
		fwrite(&mas[i], sizeof(SCAN_INFO), 1, f);
	fclose(f);
	free(mas);
	reindex(db);
}
void add_scanner(const char* db, const char* scanner_str) {
	int numb, i, j, maxId;
	char c, charnumb[127];
	SCAN_INFO tmp;
	FILE* f;
	fopen_s(&f, db, "r+");
	if ((f == NULL) || (!strlen(scanner_str))) return;
	fread(&numb, sizeof(int), 1, f);
	fread(&tmp, sizeof(SCAN_INFO), 1, f);
	maxId = tmp.id;
	for (i = 1; i < numb; i++){
		fread(&tmp, sizeof(SCAN_INFO), 1, f);
		if (maxId < tmp.id) maxId = tmp.id;
	}
	tmp.id = maxId + 1;								
	char sstr[255];
	char* nexttoken = NULL;
	strcpy_s(sstr, 255, scanner_str);
	char* newStr = strtok_s(sstr, ";", &nexttoken);
	i = 0;
	while (newStr != NULL) {
		switch (i) {
		case 0: strcpy_s(tmp.manufacturer, 127, newStr); break;
		case 1: strcpy_s(tmp.model, 127, newStr); break;
		case 2: tmp.year = atoi(newStr); break;
		case 3: tmp.price = atof(newStr); break;
		case 4: tmp.x_size = atoi(newStr); break;
		case 5: tmp.y_size = atoi(newStr); break;
		}
		newStr = strtok_s(NULL, ";", &nexttoken);
		i++;
	}
	fwrite(&tmp, sizeof(SCAN_INFO), 1, f);
	numb += 1;
	fseek(f, 0, SEEK_SET);
	fwrite(&numb, sizeof(int), 1, f);
	fclose(f);
	reindex(db);
}
enum strings stringToEnum(const char* str) {
	if (!strcmp(str, "id")) return id;
	if (!strcmp(str, "manufacturer")) return manufacturer;
	if (!strcmp(str, "model")) return model;
	if (!strcmp(str, "year")) return year;
	if (!strcmp(str, "price")) return price;
	if (!strcmp(str, "x_size")) return x_size;
	if (!strcmp(str, "y_size")) return y_size;
	return -1;
}
RECORD_SET* select(const char* db, const char* field, const char* value) {
	enum strings temp;
	int i, j, numb, replics = 0;
	RECORD_SET* bundle;
	SCAN_INFO* mas;
	SCAN_INFO* mas2;
	SCAN_INFO* res_mas;
	FILE* f;
	fopen_s(&f, db, "r");
	if ((NULL == f)||!strlen(field)||!strlen(value)) return NULL;
	fread(&numb, sizeof(int), 1, f);
	mas = (SCAN_INFO*)malloc(sizeof(SCAN_INFO) * (numb));
	mas2 = (SCAN_INFO*)malloc(sizeof(SCAN_INFO) * (numb));
	for (i = 0; i < numb; i++) {
		fread(&mas[i], sizeof(SCAN_INFO), 1, f);
	}
	fclose(f);
	temp = stringToEnum(field);
	
	switch (temp) {
	case 0:
		j = 0;
		for(i = 0; i < numb; i++)
			if (mas[i].id == atoi(value)) {
				mas2[j] = mas[i];
				j++;
			}
		break;
	case 1:
		j = 0;
		for (i = 0; i < numb; i++)
			if (!strcmp(mas[i].manufacturer, value)) {
				mas2[j] = mas[i];
				j++;
			}
		break;
	case 2:
		j = 0;
		for (i = 0; i < numb; i++)
			if (!strcmp(mas[i].model, value)) {
				mas2[j] = mas[i];
				j++;
			}
		break;
	case 3:
		j = 0;
		for (i = 0; i < numb; i++)
			if (mas[i].year == atoi(value)) {
				mas2[j] = mas[i];
				j++;
			}
		break;
	case 4:
		j = 0;
		for (i = 0; i < numb; i++)
			if (mas[i].price == atof(value)) {
				mas2[j] = mas[i];
				j++;
			}
		break;
	case 5:
		j = 0;
		for (i = 0; i < numb; i++)
			if (mas[i].x_size == atoi(value)) {
				mas2[j] = mas[i];
				j++;
			}
		break;
	case 6:
		j = 0;
		for (i = 0; i < numb; i++)
			if (mas[i].y_size == atoi(value)) {
				mas2[j] = mas[i];
				j++;
			}
		break;
	default: j = 0; break;
	}
	if (0 == j) {
		free(mas);
		free(mas2);
		return NULL;
	}
	bundle = (RECORD_SET*)malloc(sizeof(RECORD_SET));
	res_mas = (SCAN_INFO*)malloc(sizeof(SCAN_INFO) * j);
	for (i = 0; i < j; i++)
		res_mas[i] = mas2[i];
	bundle->recs = res_mas;
	free(mas); 
	free(mas2);
	bundle->rec_nmb = j;
	return bundle;
}
void print_rec_set(RECORD_SET* rs) {
	if (rs == NULL) return;
	int i, records;
	records = rs->rec_nmb;
	printf("Print_rec_set : \n");
	for (i = 0; i < records; i++) {
		printf(" %d %s %s %d %lf %d %d \n", rs->recs[i].id, rs->recs[i].manufacturer, rs->recs[i].model, rs->recs[i].year, rs->recs[i].price,
			rs->recs[i].x_size, rs->recs[i].y_size);
	}
}
void print_db(const char* db) {
	FILE* f, *g;
	SCAN_INFO temp;
	fopen_s(&f, db, "r");
	fopen_s(&g, "Db-file.txt", "w");
	if (f == NULL) return;
	int k; 
	fread(&k, sizeof(int), 1, f);
	printf("Scanners.db : \n");
	while (fread(&temp, sizeof(SCAN_INFO), 1, f)) {
		fprintf(g, "%d %s %s %d %.3f %d %d \n", temp.id, temp.manufacturer, temp.model, temp.year, temp.price, temp.x_size, temp.y_size);
		printf(" %d %s %s %d %.3f %d %d \n", temp.id, temp.manufacturer, temp.model, temp.year, temp.price, temp.x_size, temp.y_size);
	}
	_fcloseall();
}