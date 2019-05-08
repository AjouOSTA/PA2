#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include <sys/queue.h>

static LIST_HEAD(listhead, entry) head;

struct listhead *headp = NULL;
int num_entries = 0;

struct entry {
	char name[BUFSIZ];
	int frequency;
	LIST_ENTRY(entry) entries;
};

int main(int argc, char** argv)
{
	if (argc != 2) {
		fprintf(stderr, "%s: not enough input\n", argv[0]);
		exit(1);
	}

	FILE* fp = fopen(argv[1], "r");
	char buf[4096];

	LIST_INIT(&head);

	while (fgets(buf, 4096, fp)) {
		// Preprocess: change all non-alnums into white-space,
		//             alnums to lower-case.
		int line_length = strlen(buf);

		for (int it = 0; it < line_length; ++it) {
			if (!isalnum(buf[it])) {
				buf[it] = ' ';
			} else {
				buf[it] = tolower(buf[it]);
			}
		}

		const char* WHITE_SPACE =" \t\n";
		char* tok = strtok(buf, WHITE_SPACE);

		if (tok == NULL || strcmp(tok, "") == 0) {
			continue;
		}

		do {
			if (num_entries == 0) {
				struct entry* e = malloc(sizeof(struct entry));

				strncpy(e->name, tok, strlen(tok));
				e->frequency = 1;

				LIST_INSERT_HEAD(&head, e, entries);
				num_entries++;
				continue;
			} else if (num_entries == 1) {
				int cmp = strcmp(tok, head.lh_first->name);

				if (cmp == 0) {
					head.lh_first->frequency++;
				} else if (cmp > 0) {
					struct entry* e = malloc(sizeof(struct entry));

					strncpy(e->name, tok, strlen(tok));
					e->frequency = 1;


					LIST_INSERT_AFTER(head.lh_first, e, entries);
					num_entries++;
				} else if (cmp < 0) {
					struct entry* e = malloc(sizeof(struct entry));

					strncpy(e->name, tok, strlen(tok));
					e->frequency = 1;

					LIST_INSERT_BEFORE(head.lh_first, e, entries);
					num_entries++;
				}

				continue;
			}

			struct entry* np = head.lh_first;
			struct entry* final_np = NULL;

			int last_cmp = strcmp(tok, np->name);

			if (last_cmp < 0) {
				struct entry* e = malloc(sizeof(struct entry));

				strncpy(e->name, tok, strlen(tok));
				e->frequency = 1;

				LIST_INSERT_BEFORE(np, e, entries);
				num_entries++;

				continue;

			} else if (last_cmp == 0) {
				np->frequency++;

				continue;
			}

			for (np = np->entries.le_next; np != NULL; np = np->entries.le_next) {
				int cmp = strcmp(tok, np->name);

				if (cmp == 0) {
					np->frequency++;
					break;
				} else if (last_cmp * cmp < 0) { // sign-crossing occurred
					struct entry* e = malloc(sizeof(struct entry));

					strncpy(e->name, tok, strlen(tok));
					e->frequency = 1;

					LIST_INSERT_BEFORE(np, e, entries);
					num_entries++;

					break;
				}

				if (np->entries.le_next == NULL) {
					final_np = np;
				} else {
					last_cmp = cmp;
				}
			}

			if (!np && final_np) {
				struct entry* e = malloc(sizeof(struct entry));

				strncpy(e->name, tok, strlen(tok));
				e->frequency = 1;

				LIST_INSERT_AFTER(final_np, e, entries);
				num_entries++;
			}
		} while (tok = strtok(NULL, WHITE_SPACE));
	}

	struct entry** entries_for_summary = malloc(sizeof(struct entry*) * num_entries);
	int idx = 0;

	for (struct entry* np = head.lh_first; np != NULL; np = np->entries.le_next) {
		entries_for_summary[idx] = np;
		idx++;
	}

	struct entry** reduced_entries = malloc(sizeof(struct entry*) * num_entries * num_entries);
	memset(reduced_entries, 0, num_entries * num_entries);
	int* n_entries = malloc(sizeof(int) * num_entries);
	memset(n_entries, 0, num_entries);

	for (struct entry* np = head.lh_first; np != NULL; np = np->entries.le_next) {
		reduced_entries[np->frequency * num_entries + n_entries[np->frequency]] = np;
		n_entries[np->frequency]++;
	}

	free(entries_for_summary);

	for (int it = 1; it < num_entries; ++it) {
		for (int jt = 0; jt < n_entries[num_entries - it]; ++jt) {
			struct entry* e = reduced_entries[(num_entries - it) * num_entries + jt];
			printf("%s %d\n", e->name, num_entries - it);
		}
	}

	free(reduced_entries);
	free(n_entries);

	while (head.lh_first != NULL) {
		LIST_REMOVE(head.lh_first, entries);
	}

	fclose(fp);

	return 0;
}
