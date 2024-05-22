#!/usr/bin/python3
"""Function to return number of subscribers
on a given Reddit subreddit."""
import requests


def number_of_subscribers(subreddit):
    """Return number of subscribers on a given subreddit."""
    url = "https://www.reddit.com/r/{}/about.json".format(subreddit)
    user_agent = "reddit_user"
    headers = {
        "User-Agent": user_agent
    }
    resp = requests.get(url, headers=headers, allow_redirects=False)
    if resp.status_code == 404:
        return 0
    results = resp.json().get("data")
    return results.get("subreddit_subscribers")
