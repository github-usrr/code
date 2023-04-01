package com.task5.task5;

import org.springframework.http.MediaType;
import org.springframework.web.bind.annotation.*;

import java.awt.*;
import java.util.*;

@RestController
public class Controller {

    @PostMapping(value="/user/signup", consumes=MediaType.APPLICATION_JSON_VALUE)
    public String signup(@RequestBody User user) {

        if ( registered.containsKey(user.getUsername()) )
            return "User hasn't been registered, this username already exists";

        registered.put(user.getUsername(), user);
        return "User has been successfully registered";
    }

    @PostMapping(value="/user/login", consumes=MediaType.APPLICATION_JSON_VALUE)
    public String login(@RequestBody User user) {

        String name = user.getUsername();

        if ( !registered.containsKey(name) )
            return "Login failed. Wrong username";

        if ( !registered.get(name).getPassword().equals(user.getPassword()) )
            return "Login failed. Wrong password";

        UUID session_id   = UUID.randomUUID();
        UUID access_token = UUID.randomUUID();

        sessions.put(session_id, user);
        tokens.put(access_token, user);

        return "session_id=" + session_id.toString() +
                "<br>access_token=" + access_token.toString();
    }

    @GetMapping("/user/logout")
    @ResponseBody
    public String logout(@RequestParam String session_id) {

        String errStr = "Error! Incorrect session_id";

        UUID sessionUuid;
        try {
            sessionUuid = UUID.fromString(session_id);
        } catch (IllegalArgumentException e) {
            return errStr;
        }

        if ( !sessions.containsKey(sessionUuid) )
            return errStr;

        // remove user from sessions
        User user = sessions.remove(sessionUuid);

        // remove user from tokens
        tokens.values().remove(user);

        return "Logged out";
    }

    @GetMapping("/os/memory")
    @ResponseBody
    public String memoryUsage(@RequestParam String access_token) {

        String errStr = "Incorrect access_token";

        UUID tokenUuid;
        try {
            tokenUuid = UUID.fromString(access_token);
        } catch (IllegalArgumentException e) {
            return errStr;
        }

        if ( tokens.containsKey(tokenUuid) )
            return "RAM:" +
                    "<br>Total (Gb): 4" +
                    "<br>In Use (Gb): 2";
        return errStr;
    }

    @GetMapping("/os/cpu")
    @ResponseBody
    public String cpuUsage(@RequestParam String access_token) {

        String errStr = "Incorrect access_token";

        UUID tokenUuid;
        try {
            tokenUuid = UUID.fromString(access_token);
        } catch (IllegalArgumentException e) {
            return errStr;
        }

        if ( tokens.containsKey(tokenUuid) )
            return "CPU Usage (%): 50";
        return errStr;
    }

    private Map<String, User> registered = new HashMap<String, User>();
    private Map<UUID, User>     sessions = new HashMap<UUID, User>();
    private Map<UUID, User>       tokens = new HashMap<UUID, User>();
}

