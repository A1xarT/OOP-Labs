#include "scanner.h"

int main() {
	create_db("Scanners.csv", "Scanners.db");
	print_db("Scanners.db");
	reindex("Scanners.db");
	add_scanner("Scanners.db", "Asus;AS1055;2009;99.99;210;297");
	print_db("Scanners.db");
	del_scanner("Scanners.db", 2);
	print_db("Scanners.db");
	RECORD_SET* rs = select("Scanners.db", "manufacturer", "Asus");
	print_rec_set(rs);
	rs = get_recs_by_index("Scanners.db", "manufacturer");
	print_rec_set(rs);

	return 0;
}