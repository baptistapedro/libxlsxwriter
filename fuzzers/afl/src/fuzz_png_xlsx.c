#include <stdio.h>
#include <string.h>
#include "xlsxwriter.h"

// Demo modified to receive image input from argv, afl fuzzer

int main(int argc, char **argv) {
 
    if (argc < 2) {
      printf("Usage: bin input\n");
      return 1;
    }
    /* Create a new workbook and add a worksheet. */
    lxw_workbook  *workbook  = workbook_new("demo.xlsx");
    lxw_worksheet *worksheet = workbook_add_worksheet(workbook, NULL);

    /* Add a format. */
    lxw_format *format = workbook_add_format(workbook);

    /* Set the bold property for the format */
    format_set_bold(format);

    /* Change the column width for clarity. */
    worksheet_set_column(worksheet, 0, 0, 20, NULL);

    /* Write some simple text. */
    worksheet_write_string(worksheet, 0, 0, "Hello", NULL);

    /* Text with formatting. */
    worksheet_write_string(worksheet, 1, 0, "World", format);

    /* Write some numbers. */
    worksheet_write_number(worksheet, 2, 0, 123,     NULL);
    worksheet_write_number(worksheet, 3, 0, 123.456, NULL);

    /* Insert an image. */
    worksheet_insert_image(worksheet, 1, 2, argv[1]);

    workbook_close(workbook);

    return 0;
}
