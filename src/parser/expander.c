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

static void handle_variable_expansion(char **input_ptr, t_buffer *buf, t_env_lst *env)
{
    char *input = *input_ptr;
    char *var_name;
    char *var_value;
    int len = 0;

    input++; 
    if (input[0] == '?')
    {
        var_value = ft_itoa(g_signal_received); 
        append_str(buf, var_value);
        free(var_value);
        *input_ptr += 2; 
        return;
    }
    
    while (ft_isalnum(input[len]) || input[len] == '_')
        len++;

    if (len == 0) 
    {
        append_char(buf, '$');
        *input_ptr += 1;
        return;
    }

    var_name = ft_substr(input, 0, len);
    var_value = get_env_value(var_name, env);
    if (var_value)
        append_str(buf, var_value);
    
    free(var_name);
    *input_ptr += (len + 1); 
}

char *expand_line(char *line, t_env_lst *env)
{
    t_buffer buf;
    char quote_type = 0; 

    init_buffer(&buf, ft_strlen(line) + 128);
    while (*line)
    {
        if (quote_type) 
        {
            if (*line == quote_type)
                quote_type = 0; 
            else if (*line == '$' && quote_type == '"')
                handle_variable_expansion(&line, &buf, env);
            else
            {
                append_char(&buf, *line);
                line++;
            }
        }
        else 
        {
            if (*line == '\'' || *line == '"')
            {
                quote_type = *line; 
                line++;
            }
            else if (*line == '$')
                handle_variable_expansion(&line, &buf, env);
            else
            {
                append_char(&buf, *line);
                line++;
            }
        }
    }
    return (buf.data);
}