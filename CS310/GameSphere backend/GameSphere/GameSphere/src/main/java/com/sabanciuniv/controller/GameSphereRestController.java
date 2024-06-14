package com.sabanciuniv.controller;


import java.util.Arrays;
import java.util.List;
import java.util.stream.Collectors;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;
import com.sabanciuniv.model.Credentials;
import com.sabanciuniv.model.GameOnAllPlatforms;
import com.sabanciuniv.model.Platform;
import com.sabanciuniv.model.Profile;
import com.sabanciuniv.model.ProfilePayload;
import com.sabanciuniv.model.Ratings;
import com.sabanciuniv.model.User;
import com.sabanciuniv.model.UserPayload;
import com.sabanciuniv.repo.CredentialsRepo;
import com.sabanciuniv.repo.GameOnAllPlatformsRepo;
import com.sabanciuniv.repo.ProfileRepo;
import com.sabanciuniv.repo.UserRepo;
import jakarta.annotation.PostConstruct;

@RestController
@RequestMapping("/GameSphere")
public class GameSphereRestController 
{

	@Autowired
    private UserRepo userRepository;
    @Autowired
    private ProfileRepo profileRepository;
    @Autowired
    private CredentialsRepo credentialsRepository;
    @Autowired
    private GameOnAllPlatformsRepo gameOnAllPlatformsRepo;

    private static final Logger logger = LoggerFactory.getLogger(GameSphereRestController.class);

    @PostConstruct
    public void init() 

    {
    	logger.info("DataBase is empty, initializing...");
        // Initialize Credentials
        if (credentialsRepository.count() == 0) 
        {
        	//Create and save credentials to the database
            Credentials creds1 = new Credentials("user1","pass1");
            Credentials creds2 = new Credentials("user2","pass2");
            Credentials creds3 = new Credentials("user3","pass3");
            credentialsRepository.save(creds1);
            credentialsRepository.save(creds2);
            credentialsRepository.save(creds3);
            
            //Create and save games to the database
            GameOnAllPlatforms game1 = new GameOnAllPlatforms("Elden Ring", "An epic RPG game.", new Platform(40,30,0,0), new Ratings(9, 8, 10, 7, 6, 5, 3, 10));
            GameOnAllPlatforms game2 = new GameOnAllPlatforms("GTA 5", "Best game ever.", new Platform(27,15,7,0), new Ratings(6, 3, 7, 4, 10, 7, 6, 4));
            GameOnAllPlatforms game3 = new GameOnAllPlatforms("Witcher 3", "Incredible horse riding skills lol!", new Platform(18,0,70,0), new Ratings(2, 5, 2, 2, 3, 1, 2, 1));
            GameOnAllPlatforms game4 = new GameOnAllPlatforms("Skyrim", "Dragons and freedom.", new Platform(35, 20, 15, 0), new Ratings(7, 7, 8, 6, 9, 4, 5, 6));
            GameOnAllPlatforms game5 = new GameOnAllPlatforms("Fallout 4", "Post-apocalyptic exploration.", new Platform(50, 20, 10, 5), new Ratings(8, 6, 9, 5, 7, 3, 4, 7));
            GameOnAllPlatforms game6 = new GameOnAllPlatforms("Dark Souls", "Prepare to die... a lot.", new Platform(25, 15, 5, 0), new Ratings(10, 9, 10, 8, 2, 10, 1, 10));
            GameOnAllPlatforms game7 = new GameOnAllPlatforms("Red Dead Redemption 2", "A cowboy's life for me.", new Platform(22, 25, 18, 0), new Ratings(10, 10, 10, 9, 8, 5, 4, 9));
            GameOnAllPlatforms game8 = new GameOnAllPlatforms("Cyberpunk 2077", "Futuristic yet buggy.", new Platform(40, 30, 0, 10), new Ratings(5, 4, 7, 3, 7, 2, 6, 8));
            GameOnAllPlatforms game9 = new GameOnAllPlatforms("Fortnite", "Battle Royale with builds.", new Platform(60, 45, 20, 15), new Ratings(4, 6, 5, 4, 10, 6, 9, 4));
            GameOnAllPlatforms game10 = new GameOnAllPlatforms("League of Legends", "MOBA with toxic community.", new Platform(90, 60, 30, 20), new Ratings(6, 9, 3, 7, 1, 8, 2, 5));
            gameOnAllPlatformsRepo.saveAll(Arrays.asList(game1, game2, game3, game4, game5, game6, game7, game8, game9, game10)); // Save all games to the database

            //Create and save profiles to the database
            Profile profile1 = new Profile(100, 40, Arrays.asList(game1, game3, game7), "gametag1");
            Profile profile2 = new Profile(123, 78, Arrays.asList(game2, game4, game9, game10), "gametag2");
            Profile profile3 = new Profile(99, 404, Arrays.asList(game5, game6, game8), "gametag3");
            profileRepository.save(profile1);
            profileRepository.save(profile2);
            profileRepository.save(profile3);
            
            //get the credential in a capsulated and safe way
            Credentials user1Creds = credentialsRepository.findByUserName("user1");
            Credentials user2Creds = credentialsRepository.findByUserName("user2");
            Credentials user3Creds = credentialsRepository.findByUserName("user3");
            //Create and save Users to the database
            User user1 = new User(profile1, user1Creds);
            User user2 = new User(profile2, user2Creds);
            User user3 = new User(profile3, user3Creds);
            userRepository.save(user1);
            userRepository.save(user2);
            userRepository.save(user3);
            
            logger.info("Initializating complete!");
            
        }
    }
    
    @GetMapping("/Users")
    public List<User> users()
    {
    	return userRepository.findAll();
    }
    
    @GetMapping("/Credentials")
    public List<Credentials> credentials()
    {
    	return credentialsRepository.findAll();
    }
    
    
    @GetMapping("/Games")
    public List<GameOnAllPlatforms> games()
    {
    	return gameOnAllPlatformsRepo.findAll();
    }
    
    @GetMapping("/Profiles")
    public List<Profile> profiles() 
    {
    	return profileRepository.findAllWithGames();
        
    }
    
    @PostMapping("/Credentials/save")
    public Credentials saveCredentials(@RequestBody Credentials credentials)
    {
    	Credentials savedCredentials = credentialsRepository.save(credentials);
    	return savedCredentials;
    }
    
    @PostMapping("/Games/save")
    public GameOnAllPlatforms saveGamesAllPlatforms(@RequestBody GameOnAllPlatforms game)
    {
    	GameOnAllPlatforms savedGameOnAllPlatforms = gameOnAllPlatformsRepo.save(game);
    	return savedGameOnAllPlatforms;
    }
    
    @PostMapping("/Profile/save")
    public Profile saveProfile(@RequestBody ProfilePayload payload) 
    {
        // Extract game IDs from the payload
        List<String> gameIds = payload.getGamesId();

        // Create a list of GameOnAllPlatforms objects using the game IDs
        List<GameOnAllPlatforms> games = gameIds.stream()
            .map(gameId -> {
                GameOnAllPlatforms game = new GameOnAllPlatforms();
                game.setId(gameId); // Assign the ID to each game
                return game;
            })
            .collect(Collectors.toList());

        // Creating the profile to save
        Profile profileToSave = new Profile(
            payload.getFollowerCount(),
            payload.getFollowingCount(),
            games,
            payload.getNickName()
        );

        // Saving the profile in the database
        Profile profileSaved = profileRepository.save(profileToSave);

        return profileSaved;
    }
    
    
    @PostMapping("/Users/save")
	public User saveUser(@RequestBody UserPayload payload)
    {
    	Credentials credentials = new Credentials();
    	credentials.setId(payload.getCredentialsId());
    	
    	Profile profile = new Profile();
    	profile.setId(payload.getProfileId());
    	
    	User userToSaveUser = new User(profile, credentials);
    	
    	User userSaved = userRepository.save(userToSaveUser);
    	return userSaved;
    }
     
     
}
