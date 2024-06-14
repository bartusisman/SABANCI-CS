package com.sabanciuniv.repo;

import org.springframework.data.mongodb.repository.MongoRepository;

import com.sabanciuniv.model.Credentials;

public interface CredentialsRepo extends MongoRepository<Credentials, String> {

	Credentials findByUserName(String string);

}
