// #include <iostream>

// int main()
// {
//     const char *c = "suraj";
//     printf("c = %s\n", c);
//     c[0] = 'f';
//     printf("c = %s\n", c);

//     return 0;
// }

// // // different initializations :)
// // #include <iostream>

// // class human
// // {
// // public:
// //     int age;

// //     human()
// //     {
// //         std::cout << "default constructor" << std::endl;
// //     }

// //     human(int val) : age(val)
// //     {
// //         std::cout << "parameterized constructor" << std::endl;
// //     }

// //     human(const human &h) : age(h.age)
// //     {
// //         std::cout << "copy constructor" << std::endl;
// //     }
// // };

// // int main()
// // {
// //     int default_int;
// //     printf("default_int = %d\n", default_int);

// //     human default_obj;
// //     printf("default_obj = %d\n\n", default_obj.age);

// //     int para_int(2);
// //     printf("para_int = %d\n", para_int);

// //     human para_obj(2);
// //     printf("para_obj = %d\n\n", para_obj.age);

// //     // direct initialization is nothing but parameterized in a way
// //     int direct_int(3);
// //     printf("direct_int = %d\n", direct_int);

// //     human direct_obj(3);
// //     printf("direct_obj = %d\n\n", direct_obj.age);

// //     // copy initialization
// //     int copy_int = 4;
// //     printf("copy_int = %d\n", copy_int);

// //     human copy_obj(direct_obj);
// //     printf("copy_obj = %d\n", copy_obj.age);

// //     human copy_obj2 = para_obj;
// //     printf("copy_obj2 = %d\n\n", copy_obj2.age);

// //     // conversion constructor
// //     human conversion_obj = 5;
// //     printf("conversion_obj = %d\n\n", conversion_obj.age);

// //     return 0;
// // }

// // // functional pointer

// // // #include <iostream>

// // // int add(int a, int b)
// // // {
// // //     return a + b;
// // // }

// // // int subtract(int a, int b)
// // // {
// // //     return a - b;
// // // }

// // // int calculate(int a, int b, int (*operation)(int c, int d))
// // // {
// // //     return operation(a, b);
// // // }

// // // int main()
// // // {
// // //     int a = 10, b = 20;
// // //     int sum = calculate(a, b, add);
// // //     int diff = calculate(a, b, subtract);
// // //     std::cout << sum << " " << diff << std::endl;
// // //     return 0;
// // // }

// // // #include <stdio.h>

// // // int sum(int &a, int b)
// // // {
// // //     return a + b;
// // // }
// // // int main()
// // // {
// // //     int a = 5;
// // //     const int b = 7;

// // //     printf("sum = %d\n", sum(a, 3));
// // //     return 0;
// // // }