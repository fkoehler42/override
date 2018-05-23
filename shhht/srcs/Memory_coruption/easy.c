/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   easy.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wandre <wandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/06 10:03:37 by wandre            #+#    #+#             */
/*   Updated: 2016/01/06 11:26:54 by wandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	gcc -m32 -o Easy-memory_coruption easy.c
*/

#include <stdio.h>
#include <stdlib.h>

int
main(int argc, char *argv[]) {
	
	int 		input;

	printf("***********************************\n");
	printf("* 	     -Level00 -		  *\n");
	printf("***********************************\n");

	printf("Password:");
	scanf("%d", &input);

	if (input == 0x149c) {
		printf("\nAuthenticated!\n");
		system("/bin/sh");
	} else {
		printf("\nInvalid Password!\n");
		return EXIT_FAILURE;
	}

	
	return EXIT_SUCCESS;
}
