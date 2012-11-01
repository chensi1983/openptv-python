/* Unit tests for reading and writing parameter files. */

#include <check.h>
#include <stdlib.h>
#include "../src_c/parameters.h"

START_TEST(test_read_sequence_par)
{
    int cam;
    char fname[SEQ_FNAME_MAX_LEN];
    sequence_par *seqp;

    seqp = read_sequence_par("testing_fodder/parameters/sequence.par");
    
    for (cam = 0; cam < 4; cam++) {
        printf("%s", seqp->img_base_name[cam]);
        sprintf(fname, "dumbbell/cam%d_Scene77_", cam + 1);
        fail_unless(strncmp(fname, seqp->img_base_name[cam],
            SEQ_FNAME_MAX_LEN - 1) == 0);
    }
    fail_unless(seqp->first == 497);
    fail_unless(seqp->last == 597);
}
END_TEST


Suite* fb_suite(void) {
    Suite *s = suite_create ("Parameters handling");

    TCase *tc = tcase_create ("Read sequence parameters");
    tcase_add_test(tc, test_read_sequence_par);
    suite_add_tcase (s, tc);

    return s;
}

int main(void) {
    int number_failed;
    Suite *s = fb_suite ();
    SRunner *sr = srunner_create (s);
    srunner_run_all (sr, CK_ENV);
    number_failed = srunner_ntests_failed (sr);
    srunner_free (sr);
    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
