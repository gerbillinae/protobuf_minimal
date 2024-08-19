#include <iostream>
#include "generated/addressbook.pb.h"

void test_serialize_person() {
    std::cout << std::endl << "Testing Person Serialization" << std::endl;

    // Create a new Person object
    tutorial::Person person;
    person.set_name("John");
    person.set_id(123);
    person.set_email("john@example.com");

    // Add a phone number
    {
        tutorial::Person::PhoneNumber *phone = person.add_phones();
        phone->set_number("555-4321");
        phone->set_type(tutorial::Person::PHONE_TYPE_HOME);
    }

    // Serialize to string
    std::string serialized_person;
    person.SerializeToString(&serialized_person);

    // Deserialize from string
    tutorial::Person deserialized_person;
    if (deserialized_person.ParseFromString(serialized_person)) {
        std::cout << "Name: " << deserialized_person.name() << std::endl;
        std::cout << "ID: " << deserialized_person.id() << std::endl;
        std::cout << "Email: " << deserialized_person.email() << std::endl;
        for (int i = 0; i < deserialized_person.phones_size(); i++) {
            const tutorial::Person::PhoneNumber& p = deserialized_person.phones(i);
            std::cout << "Phone: " << p.number() << " (" << p.type() << ")" << std::endl;
        }
    }
}

void test_serialize_address_book() {
    std::cout << std::endl << "Testing AddressBook Serialization" << std::endl;

    // Create a new Person object
    tutorial::Person person_1;
    person_1.set_name("Bob");
    person_1.set_id(1);
    person_1.set_email("bob@example.com");

    // Add a phone number
    {
        tutorial::Person::PhoneNumber *phone = person_1.add_phones();
        phone->set_number("555-4321");
        phone->set_type(tutorial::Person::PHONE_TYPE_HOME);
    }

    // Create an AddressBook object
    tutorial::AddressBook address_book;
    *(address_book.add_people()) = person_1;

    auto* person_2 = address_book.add_people();

    person_2->set_name("Alice");
    person_2->set_id(2);
    person_2->set_email("alice@example.com");

    // Add a phone number
    {
        tutorial::Person::PhoneNumber *phone = person_2->add_phones();
        phone->set_number("324-3353");
        phone->set_type(tutorial::Person::PHONE_TYPE_MOBILE);
        tutorial::Person::PhoneNumber *phone2 = person_2->add_phones();
        phone2->set_number("342-3588");
        phone2->set_type(tutorial::Person::PHONE_TYPE_WORK);

    }

    // Serialize to string
    std::string serialized_address_book;
    address_book.SerializeToString(&serialized_address_book);

    // Deserialize from string
    tutorial::AddressBook deserialized_address_book;

    if (deserialized_address_book.ParseFromString(serialized_address_book)) {
        for (int i = 0; i < deserialized_address_book.people_size(); i++)
        {
            const tutorial::Person& person = deserialized_address_book.people(i);
            std::cout << "Name: " << person.name() << std::endl;
            std::cout << "ID: " << person.id() << std::endl;
            std::cout << "Email: " << person.email() << std::endl;
            for (int j = 0; j < person.phones_size(); j++) {
                const tutorial::Person::PhoneNumber& phone = person.phones(j);
                std::cout << "Phone: " << phone.number() << " (" << phone.type() << ")" << std::endl;
            }
        }
    }
}

int main() {

    // Validate that the protobuf library we are linked against and the protoc that generated our files match.
    GOOGLE_PROTOBUF_VERIFY_VERSION;

    test_serialize_person();

    test_serialize_address_book();

    // You only need to call this if you're writing a dynamic library that should clean-up after itself.
    // Otherwise, you can simply let the protobuf allocations live until the program is shutdown.
    google::protobuf::ShutdownProtobufLibrary();

    return 0;
}