package com.sabanciuniv.repo;

import org.springframework.data.mongodb.repository.MongoRepository;

import com.sabanciuniv.model.User;

public interface UserRepo extends MongoRepository<User, String>{

}
