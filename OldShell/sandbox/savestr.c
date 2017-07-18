
		while (token[i])
		{
			for (j = 0; delim[j]; j++)
			{
				if (token[i] == delim[j])
				{
					token[i] = '\0';
					i++;
					return (token);
				}
			}

		}
	token[i] = '\0';
					i++;
					return (token);

i++;
 46                                         token2 = strdup(&token[i]);
 47                                         i--;
 48                                         token[i] = '\0';
 49                                         token = realloc(token, i);
 50                                         if (token == NULL)
 51                                                 return (NULL);
 52      					 return (token);
