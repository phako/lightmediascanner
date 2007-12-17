#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <lightmediascanner.h>
#include <stdio.h>
#include <stdlib.h>

void
usage(const char *prgname)
{
    fprintf(stderr,
            "Usage:\n"
            "\t%s <commit-interval> <slave-timeout> <db-path> <parser> "
            "<charset> <scan-path>\n"
            "\n",
            prgname);
}

int
main(int argc, char *argv[])
{
    char *db_path, *parser_name, *charset, *scan_path;
    lms_t *lms;
    lms_plugin_t *parser;
    int commit_interval, slave_timeout;

    if (argc < 6) {
        usage(argv[0]);
        return 1;
    }

    commit_interval = atoi(argv[1]);
    slave_timeout = atoi(argv[2]);
    db_path = argv[3];
    parser_name = argv[4];
    charset = argv[5];
    scan_path = argv[6];

    lms = lms_new(db_path);
    if (!lms) {
        fprintf(stderr,
                "ERROR: could not create light media scanner for DB \"%s\".\n",
                db_path);
        return -1;
    }

    lms_set_commit_interval(lms, commit_interval);
    lms_set_slave_timeout(lms, slave_timeout);

    parser = lms_parser_find_and_add(lms, parser_name);
    if (!parser) {
        fprintf(stderr, "ERROR: could not create parser \"%s\".\n",
                parser_name);
        lms_free(lms);
        return -2;
    }

    if (lms_charset_add(lms, charset) != 0) {
        fprintf(stderr, "ERROR: could not add charset '%s'\n", charset);
        lms_free(lms);
        return -3;
    }

    if (lms_check(lms, scan_path) != 0) {
        fprintf(stderr, "ERROR: checking \"%s\".\n", scan_path);
        lms_free(lms);
        return -4;
    }

    if (lms_process(lms, scan_path) != 0) {
        fprintf(stderr, "ERROR: processing \"%s\".\n", scan_path);
        lms_free(lms);
        return -5;
    }

    if (lms_free(lms) != 0) {
        fprintf(stderr, "ERROR: could not close light media scanner.\n");
        return -6;
    }

    return 0;
}