#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>

typedef struct s_map {
    size_t rows;
    size_t cols;
    char empty_c;
    char obst_c;
    char full_c;
    char **grid;
} t_map;

static int parse_header(FILE *f, t_map *m) {
    size_t rows = 0;
    char e = 0, o = 0, x = 0;

    int n = fscanf(f, " %zu %c %c %c\n", &rows, &e, &o, &x);
    if (n != 4) return -1;
    if (rows == 0) return -1;
    if (e == o || e == x || o == x) return -1;

    m->rows = rows;
    m->empty_c = e;
    m->obst_c  = o;
    m->full_c  = x;
    return 0;
}

static int read_lines(FILE *f, t_map *m) {
    m->grid = (char **)calloc(m->rows, sizeof(char *));
    if (!m->grid) return -1;

    char *line = NULL;
    size_t cap = 0;
    ssize_t len;
    m->cols = 0;

    for (size_t r = 0; r < m->rows; ++r) {
        len = getline(&line, &cap, f);
        if (len < 0) { return -1; }
        if (len == 0) { return -1; }

        if (line[len - 1] != '\n') { return -1; }
        line[len - 1] = '\0';
        len -= 1;

        if (len <= 0) { return -1; }

        if (r == 0) {
            m->cols = (size_t)len;
        } else if ((size_t)len != m->cols) {
            return -1;
        }

        for (size_t c = 0; c < m->cols; ++c) {
            char ch = line[c];
            if (!(ch == m->empty_c || ch == m->obst_c)) {
                return -1;
            }
        }

        m->grid[r] = (char *)malloc(m->cols + 1);
        if (!m->grid[r]) { return -1; }
        for (size_t c = 0; c <= m->cols; ++c) {
            m->grid[r][c] = line[c];
        }
    }
    return 0;
}

static int parse_map(FILE *f, t_map *out) {
    out->rows = 0;
    out->cols = 0;
    out->empty_c = 0;
    out->obst_c = 0;
    out->full_c = 0;
    out->grid = NULL;

    if (parse_header(f, out) != 0) return -1;
    if (read_lines(f, out) != 0) {
        return -1;
    }
    return 0;
}

static int contient_obstacle(const t_map *m, size_t x0, size_t y0, size_t taille) {
    size_t x_end = x0 + taille;
    size_t y_end = y0 + taille;
    for (size_t x = x0; x < x_end; ++x) {
        for (size_t y = y0; y < y_end; ++y) {
            if (m->grid[x][y] == m->obst_c) {
                return 1;
            }
        }
    }
    return 0;
}

static void fill_and_print(t_map *m, size_t best_x, size_t best_y, size_t best_size) {
    if (best_size > 0) {
        for (size_t i = 0; i < best_size; ++i) {
            for (size_t j = 0; j < best_size; ++j) {
                m->grid[best_x + i][best_y + j] = m->full_c;
            }
        }
    }
    for (size_t r = 0; r < m->rows; ++r) {
        fputs(m->grid[r], stdout);
        fputc('\n', stdout);
    }
}

static void solve_naive_and_print(t_map *m) {
    size_t best_size = 0;
    size_t best_x = 0;
    size_t best_y = 0;

    for (size_t x = 0; x < m->rows; ++x) {
        for (size_t y = 0; y < m->cols; ++y) {
            size_t size_try = 1;
            while (x + size_try <= m->rows && y + size_try <= m->cols) {
                if (contient_obstacle(m, x, y, size_try)) {
                    break;
                }
                if (size_try > best_size) {
                    best_size = size_try;
                    best_x = x;
                    best_y = y;
                }
                size_try += 1;
            }
        }
    }

    fill_and_print(m, best_x, best_y, best_size);
}

static int process_stream(FILE *f) {
    t_map m;
    if (parse_map(f, &m) != 0) {
        fputs("map error\n", stderr);
        return -1;
    }
    solve_naive_and_print(&m);
    return 0;
}

static int process_file(const char *path) {
    FILE *fp = fopen(path, "r");
    if (!fp) {
        fputs("map error\n", stderr);
        return -1;
    }
    int rc = process_stream(fp);
    fclose(fp);
    return rc;
}

int main(int argc, char **argv) {
    if (argc <= 1) {
        (void)process_stream(stdin);
        fputc('\n', stdout);
        return 0;
    }
    for (int i = 1; i < argc; ++i) {
        (void)process_file(argv[i]);
        fputc('\n', stdout);
    }
    return 0;
}
