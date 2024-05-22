#!/usr/bin/python3
"""Function to print 10 hot posts on a  Reddit subreddit."""
import requests


def top_ten(subreddit):
    """Prints the 10 hottest posts on a given subreddit."""
    url = "https://www.reddit.com/r/{}/hot/.json".format(subreddit)
    user_agent = "redit_user"
    headers = {
        "User-Agent": user_agent
    }
    params = {
        "limit": 10
    }
    resp = requests.get(url, headers=headers, params=params,
                        allow_redirects=False)
    if resp.status_code == 404:
        print("None")
    results = resp.json().get("data")
    for x in results.get("children"):
        print(x.get("data").get("title"))
