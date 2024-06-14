package com.sabanciuniv.repo;

import org.springframework.data.mongodb.repository.MongoRepository;

import com.sabanciuniv.model.GameOnAllPlatforms;

public interface GameOnAllPlatformsRepo extends MongoRepository<GameOnAllPlatforms, String> {

}
