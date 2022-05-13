#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include <stdint.h>
#include "xlsxwriter.h"

// Demo modified to receive image input from argv, afl fuzzer
// worksheet_write_string fuzz

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
 
    if (data == NULL) return 1;
    char *buf = (char*)malloc(size + 1);
    memcpy(buf, data, size);
    buf[size] = '\0';

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
    worksheet_write_string(worksheet, 0, 0, buf, NULL);

    /* Text with formatting. */
    worksheet_write_string(worksheet, 1, 0, buf, format);

    /* Write some numbers. */
    worksheet_write_number(worksheet, 2, 0, 123,     NULL);
    worksheet_write_number(worksheet, 3, 0, 123.456, NULL);

    /* Insert an image. */
    //worksheet_insert_image(worksheet, 1, 2, ");

    workbook_close(workbook);
    free(buf);
    return 0;
}
