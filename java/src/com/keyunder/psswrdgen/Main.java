package com.keyunder.psswrdgen;

import java.security.SecureRandom;
import java.util.Scanner;
import java.util.List;
import java.util.Arrays;
import java.util.Collections;
import java.util.InputMismatchException;

public class Main {

    private static final int MIN_PASSWORD_LENGTH = 4;
    private static final int MAX_PASSWORD_LENGTH = 64;

    private static final String LOWER_CASE = "abcdefghijklmnopqrstuvwxyz";
    private static final String UPPER_CASE = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    private static final String NUMBERS = "0123456789";
    private static final String SPECIAL_CHARS = "!@#$%^&*()_+?[].";
    private static final String ALL_CHARS = LOWER_CASE + UPPER_CASE + NUMBERS + SPECIAL_CHARS;

    private static final SecureRandom random = new SecureRandom();

    public static void main(String[] args) {
        long timer = System.nanoTime();
        String psswrd = pwgen(askForLength(args));
        System.out.println("Generated password: " + psswrd);
        System.out.println("Password length:\t" + psswrd.length());
        timer = System.nanoTime() - timer;
        System.out.println(timer / 1_000_000);
    }

    static private String pwgen(int length) {
        if (length > MAX_PASSWORD_LENGTH) {
            System.out.println("Number too high. Defaulting to a max of " + MAX_PASSWORD_LENGTH);
            length = MAX_PASSWORD_LENGTH;
        }
        StringBuilder response = new StringBuilder();

        response.append(randomChar(LOWER_CASE))
                .append(randomChar(UPPER_CASE))
                .append(randomChar(NUMBERS))
                .append(randomChar(SPECIAL_CHARS));

        for (int i = 4; i < length; i++) {
            response.append(randomChar(ALL_CHARS));
        }

        String[] chars = response.toString().split("");
        List<String> charsAsList = Arrays.asList(chars);
        Collections.shuffle(charsAsList, random);

        return String.join("", chars);
    }

    private static int askForLength(String[] args) {
        if(args.length > 0) {
            try{
                int length = Integer.parseInt(args[0]);
                if (length >= MIN_PASSWORD_LENGTH) {
                    return length;
                }
                System.out.println("Invalid input. Defaulting to interactive mode");
            } catch (NumberFormatException ignored) {
                System.out.println("Invalid input. Defaulting to interactive mode");
            }
        }
        return askForLength();
    }

    private static int askForLength() {
        Scanner sc = new Scanner(System.in);
        int response;
        while (true) {
            try {
                System.out.println("Input length: ");
                response = sc.nextInt();
                if (response >= 4) {
                    break;
                }
                System.out.println("Invalid number. Enter " + MIN_PASSWORD_LENGTH + " or greater.");
            } catch (InputMismatchException e) {
                System.out.println("Invalid input. Please enter an integer.");
                sc.next();
            }
        }
        sc.close();
        return response;
    }

    private static char randomChar(String str) {
        int randomIndex = random.nextInt(str.length());
        return str.charAt(randomIndex);
    }
}
