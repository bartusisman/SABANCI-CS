package com.sabanciuniv.repo;

import java.util.List;

import org.springframework.data.mongodb.repository.Aggregation;
import org.springframework.data.mongodb.repository.MongoRepository;

import com.sabanciuniv.model.Profile;

public interface ProfileRepo extends MongoRepository<Profile, String> 
{
	@Aggregation({
	    "{ '$lookup': { 'from': 'gameOnAllPlatforms', 'localField': 'Games.$id', 'foreignField': '_id', 'as': 'Games' } }",
	    "{ '$project': { 'followerCount': 1, 'followingCount': 1, 'nickName': 1, 'Games': 1 } }"
	})
	List<Profile> findAllWithGames();
}
