#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <exception>
using std::exception;

namespace mtm {
    class Exception: public exception{};
    class InputError: public exception{};
    class outOfRange: public exception{};
    class InvalidDate: public exception{};
    class NegativeDays: public exception{};
    class InvalidStudent: public exception{};
    class AlreadyRegistered: public exception{};
    class NotRegistered: public exception{};
    class RegistrationBlocked: public exception{};
    class DateMismatch: public exception{};
    class InvalidNumber: public exception{};
    class InvalidInterval: public exception{};
    class NotSupported: public exception{};
    class EventAlreadyExists: public exception{};
    class EventDoesNotExist: public exception{};
    class AlreadyInvited: public exception{};
    
}

#endif //EXCEPTION_H