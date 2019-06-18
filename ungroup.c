/* Extract the files from a group file */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* File record */
typedef struct
{
    char filename[12];
    unsigned int length;
} FileRecord;

/* Program entry point */
int main(int argc, char *argv[])
{
    /* Declare variables */
    FILE *in;          /* The group file to be read */
    FILE *out;         /* The file to be written */
    char sig[13];      /* The file signature */
    unsigned int num;  /* Number of the files in the group file */
    FileRecord *files; /* The file records in the group file */
    unsigned int i;    /* Loop variable */
    char filename[13]; /* A file name */
    char *buffer;      /* The file buffer */

    /* Display a help message */
    if (argc != 2 || (argc == 2 && !strcmp(argv[1], "/?")) || (argc == 2 && !strcmp(argv[1], "-?")) || (argc == 2 && !strcmp(argv[1], "-h")) || (argc == 2 && !strcmp(argv[1], "--help")))
    {
        printf("Extracts the files from a .grp file.\n");
        printf("\n");
        printf("UNGROUP filename.grp\n");
        exit(1);
    }

    /* Open the group file */
    in = fopen(argv[1], "rb");
    if (in == NULL)
    {
        printf("Cannot open group file\n");
        exit(1);
    }

    /* Make sure the file is a group file */
    fread(sig, 1, 12, in);
    sig[12] = '\0';
    if (ferror(in))
    {
        printf("Error reading group file signature\n");
        exit(1);
    }
    else if (strncmp(sig, "KenSilverman", 12))
    {
        printf("Invalid file signature\n");
        exit(1);
    }

    /* Get the number of files in the group file */
    fread(&num, sizeof(unsigned int), 1, in);
    if (ferror(in))
    {
        printf("Error reading number of files\n");
        exit(1);
    }

    /* Allocate memory for the file table */
    printf("%d Files Found\n", num);
    files = (FileRecord *)malloc(sizeof(FileRecord) * num);
    if (files == NULL)
    {
        printf("Error allocating memory for the file table\n");
        exit(1);
    }

    /* Load the file records into memory */
    fread(files, sizeof(FileRecord), num, in);
    if (ferror(in))
    {
        printf("Error reading file table\n");
        exit(1);
    }

    /* Extract each file */
    printf("Extracting files...\n");
    for (i = 0; i < num; i++)
    {
        /* Get a null terminated file name */
        strncpy(filename, files[i].filename, 12);
        filename[12] = '\0';

        /* Display the file details*/
        printf("%s: %d Bytes\n", filename, files[i].length);

        /* Open the file for output */
        out = fopen(filename, "wb");
        if (out == NULL)
        {
            printf("Cannot open the file %s for writing\n", filename);
            exit(1);
        }

        /* Allocate the buffer */
        buffer = (char *)malloc(files[i].length);

        /* Read the buffer */
        fread(buffer, files[i].length, 1, in);

        /* Write the buffer */
        fwrite(buffer, files[i].length, 1, out);

        /* Clean up */
        free(buffer);
        fclose(out);

        /* Check for end of file */
        if (feof(in))
        {
            break;
        }
    }

    /* Clean up */
    free(files);
    fclose(in);
    return 0;
}
