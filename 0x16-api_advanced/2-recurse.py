#!/usr/bin/python3
"""Returns a list of all hot posts on a given Reddit subreddit."""
import requests


def recurse(subreddit, hot_list=[], after="", count=0):
    """Returns list of titles of all hot posts on a given subreddit."""
    url = "https://www.reddit.com/r/{}/hot/.json".format(subreddit)
    user_agent = "reddit_user"
    headers = {
        "User-Agent": user_agent
    }
    params = {
        "after": after,
        "count": count,
        "limit": 100
    }
    resp = requests.get(url, headers=headers, params=params,
                        allow_redirects=False)
    if resp.status_code == 404:
        return None

    results = resp.json().get("data")
    after = results.get("after")
    count += results.get("dist")
    for x in results.get("children"):
        hot_list.append(x.get("data").get("title"))

    if after is not None:
        return recurse(subreddit, hot_list, after, count)
    else:
        return hot_list
