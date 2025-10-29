#include "minishell.h"

typedef struct s_buffer
{
    char    *data;
    size_t  len;
    size_t  capacity;
}   t_buffer;

static void init_buffer(t_buffer *buf, size_t initial_capacity)
{
    buf->data = malloc(initial_capacity);
    if (!buf->data)
        exit(EXIT_FAILURE); 
    buf->data[0] = '\0';
    buf->len = 0;
    buf->capacity = initial_capacity;
}

static void append_char(t_buffer *buf, char c)
{
    if (buf->len + 1 >= buf->capacity)
    {
        buf->capacity *= 2;
        buf->data = realloc(buf->data, buf->capacity);
        if (!buf->data)
            exit(EXIT_FAILURE);
    }
    buf->data[buf->len++] = c;
    buf->data[buf->len] = '\0';
}

static void append_str(t_buffer *buf, const char *str)
{
    if (!str)
        return;
    while (*str)
        append_char(buf, *str++);
}

static int get_var_len(char *str)
{
    int len;

    len = 0;
    while (str[len] && (ft_isalnum(str[len]) || str[len] == '_'))
        len++;
    return (len);
}

static void expand_exit_status(char **line, t_buffer *buf)
{
    char *status_str;

    status_str = ft_itoa(g_signal_received);
    append_str(buf, status_str);
    free(status_str);
    (*line) += 1;
}

static void expand_variable(char **line, t_buffer *buf, t_env_lst *env)
{
    char    *var_name;
    char    *var_value;
    int     len;

    (*line)++;
    if (**line == '?')
        return (expand_exit_status(line, buf));
    len = get_var_len(*line);
    if (len == 0)
    {
        append_char(buf, '$');
        return ;
    }
    var_name = ft_substr(*line, 0, len);
    var_value = get_env_value(var_name, env);
    if (var_value)
        append_str(buf, var_value);
    free(var_name);
    (*line) += len;
}

static void process_single_quote(char **line, t_buffer *buf)
{
    (*line)++;
    while (**line && **line != '\'')
    {
        append_char(buf, **line);
        (*line)++;
    }
    if (**line == '\'')
        (*line)++;
}

static void process_double_quote(char **line, t_buffer *buf, t_env_lst *env)
{
    (*line)++;
    while (**line && **line != '"')
    {
        if (**line == '$')
            expand_variable(line, buf, env);
        else
        {
            append_char(buf, **line);
            (*line)++;
        }
    }
    if (**line == '"')
        (*line)++;
}

char *expand_line(char *line, t_env_lst *env)
{
    t_buffer buf;

    init_buffer(&buf, ft_strlen(line) + 128);
    while (*line)
    {
        if (*line == '\'')
            process_single_quote(&line, &buf);
        else if (*line == '"')
            process_double_quote(&line, &buf, env);
        else if (*line == '$')
            expand_variable(&line, &buf, env);
        else
        {
            append_char(&buf, *line);
            line++;
        }
    }
    return (buf.data);
}