// Constants for your Spotify API credentials
const CLIENT_ID = "5dd77ad0ff524330914a4e42ddbeee7a";
const CLIENT_SECRET = "91e395fde2374bb9ad9317f9d79e49d0";


async function searchAndPlaySong() {
  const searchInput = document.getElementById("search-input").value;
  const accessToken = await getAccessToken();

  if (accessToken) {
    const searchResults = await searchSpotify(accessToken, searchInput);
    displayResults(searchResults);
  } else {
    alert("Unable to get access token.");
  }
}

window.onload = function () {
    const script = document.createElement("script");
    script.src = "https://open.spotify.com/embed-podcast/iframe-api/v1";
    script.async = true;
    document.body.appendChild(script);
  
    script.onload = function () {
      onSpotifyIframeAPIReady();
    };
  };

async function getAccessToken() {
  const auth = btoa(`${CLIENT_ID}:${CLIENT_SECRET}`);
  const response = await fetch("https://accounts.spotify.com/api/token", {
    method: "POST",
    headers: {
      Authorization: `Basic ${auth}`,
      "Content-Type": "application/x-www-form-urlencoded",
    },
    body: "grant_type=client_credentials",
  });

  if (response.ok) {
    const data = await response.json();
    return data.access_token;
  } else {
    console.error("Error getting access token:", response.status);
    return null;
  }
}

async function searchSpotify(accessToken, query) {
  const response = await fetch(
    `https://api.spotify.com/v1/search?q=${query}&type=track`,
    {
      headers: {
        Authorization: `Bearer ${accessToken}`,
      },
    }
  );

  if (response.ok) {
    const data = await response.json();
    return data.tracks.items;
  } else {
    alert("Error searching for the song.");
    return [];
  }
}

function displayResults(results) {
    const resultsDiv = document.getElementById("results");
    resultsDiv.innerHTML = "";
  
    if (results.length === 0) {
      resultsDiv.innerHTML = "<p>No results found.</p>";
    } else {
      const ul = document.createElement("ul");
      
      const displayedResults = results.slice(0, 5);
      
      displayedResults.forEach((track) => {
        const li = document.createElement("li");
        const trackLink = document.createElement("a");
        trackLink.href = "#";
        trackLink.textContent = `${track.name} - ${track.artists[0].name}`;
        trackLink.setAttribute("data-track-uri", track.uri); 
        
        trackLink.addEventListener("click", () => {
          displaySongInfo(track);
        });
        
        li.appendChild(trackLink);
        ul.appendChild(li);
      });
      
      resultsDiv.appendChild(ul);
    }
  }
  
  // Function to display song information
function displaySongInfo(track) {
    const songInfoDiv = document.getElementById("song-info");
    songInfoDiv.innerHTML = `
      <p class="song-result"><strong>Song:</strong> ${track.name}</p>
      <p class="song-result"><strong>Artist:</strong> ${track.artists[0].name}</p>
      <p class="song-result"><strong>Album/Movie:</strong> ${track.album.name}</p>
      <p class="song-result"><strong>Producer:</strong> ${track.album.artists[0].name}</p>
      <p class="song-result">
        <a href="${track.external_urls.spotify}" target="_blank">Play on Spotify</a>
      </p>
    `;
  }
  

  

window.onSpotifyIframeApiReady = (IFrameAPI) => {
  const element = document.getElementById("spotify-player-container");
  const options = {
    uri: "https://open.spotify.com/track/698ItKASDavgwZ3WjaWjtz",
  };
  const callback = (EmbedController) => {};
  IFrameAPI.createController(element, options, callback);
};

function playSpotifyTrack(trackUri) {
  const iframe = document
    .getElementById("spotify-player-container")
    .querySelector("iframe");
  iframe.src = `https://open.spotify.com/embed/track/${trackUri}`;
}


// Event delegation to handle clicks on search results
const resultsDiv = document.getElementById("results");
resultsDiv.addEventListener("click", (event) => {
  if (event.target.tagName === "A") {
    // Extract the Spotify track URI from the link
    const trackUri = event.target.getAttribute("data-track-uri");
    if (trackUri) {
      // Play the selected track in the Spotify iframe
      playSpotifyTrack(trackUri);
    }
  }
});

// Event listener for the search button
const searchButton = document.getElementById("search-button");
searchButton.addEventListener("click", searchAndPlaySong);
