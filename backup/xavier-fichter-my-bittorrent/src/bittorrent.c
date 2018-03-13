/* Author: depott_g */

#include "bittorrent.h"
#include <string.h>

/* Function that gets the sha1 of string s in a new string */
void *mysha1(void *s, size_t length)
{
    unsigned char *new_s = s;
    unsigned char *ret = malloc(21);
    SHA1(new_s, length, ret);
    return ret;
}

/* Function that converts an int to a string */
void itoa(int n, char *buf)
{
    int cur = n;
    int len = 0;
    for (; cur > 0; cur /= 10)
        len++;
    len--;
    for (; len >= 0; len--)
    {
        buf[len] = (n % 10) + '0';
        n /= 10;
    }
}

/* Function that concatenates two strings together */
char *concat(char *s1, size_t size1, const char *s2, size_t size2)
{
    s1 = realloc(s1, size1 + size2 + 1);
    for (size_t i = 0; i < size2; i++)
        s1[size1 + i] = s2[i];
    s1[size1 + size2] = 0;
    return s1;
}

/* Function that converts the integers 1-9 to the strings "6881" to "6889" */
void portnum(int n, char buf[4])
{
    buf = "688";
    buf[3] = n + '0';
}

/* Callback function that concatenates the answer of the peer to userdata */
size_t write_callback(char *ptr, size_t size, size_t nmemb, void **userdata)
{
    *userdata = realloc(*userdata, size * nmemb);
    memcpy(*userdata, ptr, size * nmemb);
    return size * nmemb;
}

/* Function that prints the peers with the answer of the tracker */
void dump_peers(struct dictionnary *d)
{
    while (d)
    {
        if (mystrcmp(d->key, "peers"))
        {
            void *peers_v = d->value.value.string;
            unsigned char *peers = peers_v;
            int len = mystrlen(peers_v);
            int index = 0;
            for (; index < len; index += 6)
            {
                for (int i = index; i < index + 6; i++)
                {
                    if (i < index + 3)
                      printf("%u.", peers[i]);
                    else if (i == index + 3)
                      printf("%u:", peers[i]);
                    else if (i == index + 4)
                      printf("%u", peers[i+1]);
                    else
                      printf("%u\n", peers[i-1]);
                }
            }
        }
        d = d->next;
    }
}

/* Main function */
int main(int argc, char **argv)
{
    // Checks arguments number
    if (argc < 2)
    {
        fprintf(stderr, "To few arguments.\n");
        return -1;
    }

    // Parses command line to get the finenames
    struct cmdline *cl = cmd_line_parsing(argc, argv);
    if (cl->options / 2 == 1)
    {
      fprintf(stderr, "None implemented yet.\n");
      return -1;
    }
    // Parses the .torrent file in a dictionary and manages the options
    struct dictionnary *dico = torrent_parsing(cl->files[0]);
    if (!dico)
      return -1;
    if (cl->options / 2 == 2)
    {
        dictionnary_print(dico, 0);
        return 0;
    }

    // Sets the variables needed by curl
    CURL *handle = curl_easy_init();
    char *buf = NULL;
    char errbuff[CURL_ERROR_SIZE];

    // Gets the announce URL
    char *url = NULL;
    struct dictionnary *cur = dico;
    while (cur)
    {
        if (mystrcmp(cur->key, "announce"))
        {
            url = cur->value.value.string;
        }
        cur = cur->next;
    }

    // Gets the number of bytes left to download
    char *left = calloc(1, 32);
    cur = dico;
    while (cur)
    {
        if (mystrcmp(cur->key, "info"))
        {
            void *backup = cur;
            cur = cur->value.value.dictionnary;
            while (cur)
            {
                if (mystrcmp(cur->key, "length"))
                {
                    itoa(cur->value.value.integer, left);
                }
                cur = cur->next;
            }
            cur = backup;
        }
        cur = cur->next;
    }

    // Adding all the arguments to the URL
    char *info_hash = get_info_as_str(cl->files[0]);
    info_hash = mysha1(info_hash, strlen(info_hash));
    info_hash = curl_easy_escape(handle, info_hash, mystrlen(info_hash));
    url = concat(url, mystrlen(url), "?info_hash=", 11);
    url = concat(url, mystrlen(url), info_hash, mystrlen(info_hash));

    char *peer_id = "-MB2020-DEPOTTFICHTE";
    peer_id = curl_easy_escape(handle, peer_id, mystrlen(peer_id));
    url = concat(url, mystrlen(url), "&peer_id=", 9);
    url = concat(url, mystrlen(url), peer_id, mystrlen(peer_id));

    char *uploaded = "0";
    uploaded = curl_easy_escape(handle, uploaded, mystrlen(uploaded));
    url = concat(url, mystrlen(url), "&uploaded=", 10);
    url = concat(url, mystrlen(url), uploaded, mystrlen(uploaded));

    char *downloaded = "0";
    downloaded = curl_easy_escape(handle, downloaded, mystrlen(downloaded));
    url = concat(url, mystrlen(url), "&downloaded=", 12);
    url = concat(url, mystrlen(url), downloaded, mystrlen(downloaded));

    left = curl_easy_escape(handle, left, mystrlen(left));
    url = concat(url, mystrlen(url), "&left=", 6);
    url = concat(url, mystrlen(url), left, mystrlen(left));

    char *compact = "1";
    compact = curl_easy_escape(handle, compact, mystrlen(compact));
    url = concat(url, mystrlen(url), "&compact=", 9);
    url = concat(url, mystrlen(url), compact, mystrlen(compact));

    char *event = "started";
    event = curl_easy_escape(handle, event, mystrlen(event));
    url = concat(url, mystrlen(url), "&event=", 7);
    url = concat(url, mystrlen(url), event, mystrlen(event));

    // Prints then escapes the URL

    // Sets options
    // Defines the URL for the request
    curl_easy_setopt(handle, CURLOPT_URL, url);
    // Sets a callback function, called when data is received
    curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, write_callback);
    // Sets the 4th argument of write_callback
    curl_easy_setopt(handle, CURLOPT_WRITEDATA, &buf);
    // Sets a buffer that will be filled with error messages
    curl_easy_setopt(handle, CURLOPT_ERRORBUFFER, &errbuff);
    // Enables curl_easy_perform verbose mode if needed
    if (cl->options % 2)
    {
        curl_easy_setopt(handle, CURLOPT_VERBOSE, 1);
        // Sets the output stream of verbose mode to stdout
        curl_easy_setopt(handle, CURLOPT_STDERR, stdout);
    }

    // Performs the request
    curl_easy_perform(handle);


    FILE *out = fopen("tmp", "w");
    fwrite(buf, sizeof (char), mystrlen(buf), out);
    fclose(out);
    
    if (cl->options / 2 == 4)
    {
      struct dictionnary *answer = torrent_parsing("tmp");
      if (!dico)
        return -1;
      dump_peers(answer);
    }

    curl_easy_cleanup(handle);
    return 0;
}
